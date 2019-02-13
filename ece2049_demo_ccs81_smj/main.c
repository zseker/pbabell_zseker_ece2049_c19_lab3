
#include <stdio.h>
#include <stdlib.h>
#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"
#include "notes.h"
#include "ThroughTheFire.h"

// Function Prototypes
void swDelay(char numLoops);
void buildTimer(void);
void Timer_A2_ISR(void);
void playNote(int song[], int num);
void BuzzerOnFrequency(int frequency);
void initButtons(void);
char readButtons(void);
void playSong(struct note song[]);
void resetSong(struct note song[]);
// Declare globals here
enum _state{WELCOME, COUNTDOWN, SONG, WIN, LOSE};
enum CD_state{THREE, TWO, ONE, GO};
volatile unsigned int _thirtySecond = 0;
unsigned int thirtySecond = 0;
unsigned int lastThirtySecond = 0;
int currentNote = 0;
int score = 0;
int errors = 0;
// Main

#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A2_ISR(void){
    _thirtySecond++;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!

    _enable_interrupt();
    // You can then configure it properly, if desired
    enum _state state = WELCOME;
    enum CD_state CDstate = THREE;
    initLeds();
    configDisplay();
    configKeypad();
    buildTimer();
    initButtons();


    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    while (1)    // Forever loop
    {
        while(getKey() == '*'){
            BuzzerOff();
            setLeds(readButtons());
        }
        switch(state){
        case WELCOME:

            // Write some text to the display
            Graphics_drawStringCentered(&g_sContext, "Blue", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Eiffel 65", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
            if(getKey() == '*'){
                state = COUNTDOWN;
                Graphics_clearDisplay(&g_sContext);
                _thirtySecond = 0;
                thirtySecond = 0;
                score = 0;
                errors = 0;
                currentNote = 0;
                lastThirtySecond = 0;
                resetSong(blue);
            }
            Graphics_flushBuffer(&g_sContext);
            break;
        case SONG:
            playSong(blue);
            if(errors > 5){
                state = LOSE;
            }
            if(currentNote == 31){
                state = WIN;
                Graphics_clearDisplay(&g_sContext);
            }

            break;
        case WIN:
            setLeds(0xF);
            Graphics_drawStringCentered(&g_sContext, "WINNER WINNER", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "press *", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            if(getKey() == '*'){
                state = WELCOME;
                Graphics_clearDisplay(&g_sContext);
            }
            break;
        case LOSE:
            BuzzerOff();
            setLeds(0x0);
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "you suck", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "press *", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            if(getKey() == '*'){
                state = WELCOME;
                Graphics_clearDisplay(&g_sContext);
            }
            break;
        case COUNTDOWN:
            switch(CDstate){
            case THREE:
                Graphics_drawStringCentered(&g_sContext, "3...", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                setLeds(0x8);
                Graphics_flushBuffer(&g_sContext);
                //P1OUT |= (BIT0|BIT6);
                if(_thirtySecond >= 8){
                    CDstate = TWO;
                    Graphics_clearDisplay(&g_sContext);
                    //P1OUT &= ~(BIT0|BIT6);
                }
                break;
            case TWO:
                Graphics_drawStringCentered(&g_sContext, "2...", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);\
                setLeds(0x4);
                //P1OUT |= (BIT0);
                if(_thirtySecond >= 16){
                    Graphics_clearDisplay(&g_sContext);
                    CDstate = ONE;
                    //P1OUT &= ~(BIT0|BIT6);
                }
                break;
            case ONE:
                Graphics_drawStringCentered(&g_sContext, "1...", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                setLeds(0x2);
                //P1OUT |= BIT6;
                if(_thirtySecond >= 24){
                    Graphics_clearDisplay(&g_sContext);
                    CDstate = GO;
                    //P1OUT &= ~(BIT0|BIT6);
                }
                break;
            case GO:
                Graphics_drawStringCentered(&g_sContext, "GO!!", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                setLeds(0xF);
                if(_thirtySecond >= 32){
                    Graphics_clearDisplay(&g_sContext);
                    setLeds(0x0);
                    //P1OUT &= ~(BIT0|BIT6);
                    CDstate = THREE;
                    state = SONG;
                }
                break;
            }
            break;
        }
    }
}


void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    volatile unsigned int i,j;	// volatile to prevent removal in optimization
    // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;					// SW Delay
        while (i > 0)				// could also have used while (i)
            i--;
    }
}

void buildTimer(void){
    //we want to use ACLK (TASSEL_1) no clock divider,count UP
    //and max count of 1259 (+ 1 ACLK ticks)
    TA2CTL = TASSEL_1 + MC_1 + ID_0;
    TA2CCR0 = 1259;
    TA2CCTL0 = CCIE;
}

void BuzzerOnFrequency(int frequency)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = 32768/frequency;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

void initButtons(void){
    P7SEL &= ~(BIT0|BIT4);
    P3SEL &= ~BIT6;
    P2SEL &= ~BIT2;

    P7DIR &= ~(BIT0|BIT4);
    P3DIR &= ~BIT6;
    P2SEL &= ~BIT2;

    P7REN |= (BIT0|BIT4);
    P3REN |= (BIT6);
    P2REN |= (BIT2);

    P7OUT |= (BIT0|BIT4);
    P3OUT |= BIT6;
    P2OUT |= BIT2;
}

char readButtons(void){
    char inBits = 0x0;
    if(!(P3IN & BIT6))
        inBits += 0x4;
    if(!(P2IN & BIT2))
        inBits += 0x2;
    if(!((P7IN & BIT0) == 0x01))
        inBits += 0x8;
    if(!((P7IN & BIT4) == 0x10))
        inBits += 0x1;
    return inBits;
}

void playSong(struct note song[]){
    BuzzerOnFrequency(song[currentNote].pitch);
    setLeds(song[currentNote].button);
    thirtySecond = _thirtySecond;
    if(readButtons() == song[currentNote].button)
        song[currentNote].passed = 1;
    if(thirtySecond - lastThirtySecond > song[currentNote].length){
        if(currentNote > 0 & song[currentNote - 1].passed != 1)
            errors++;
        BuzzerOff();
        score += song[currentNote].passed;
        currentNote++;
        lastThirtySecond = _thirtySecond;
    }
}

void resetSong(struct note song[]){
    int i = 0;
    for(i = 0; i<31; i++){
        song[i].passed = 0;
    }
}
