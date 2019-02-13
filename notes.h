
/*
 * notes.h
 *
 *  Created on: Jan 30, 2019
 *      Author: pbabell
 *
 *      a set of frequency defines for tones, 3 octaves
 */

#ifndef NOTES_H_
#define NOTES_H_

struct note{
    unsigned int pitch;
    unsigned int length;
    char button;
    int passed;
};

#define C3  130
#define Cs3 139
#define D3  147
#define Eb3 156
#define E3  165
#define F3  175
#define Fs3 185
#define G3  196
#define Gs3 208
#define A3  220
#define Bb3 233
#define B3  247

#define C4  262
#define Cs4 277
#define D4  294
#define Eb4 311
#define E4  330
#define F4  349
#define Fs4 370
#define G4  392
#define Gs4 415
#define Ab4 415
#define A4  440
#define Bb4 466
#define B4  494

#define C5  523
#define Cs5 554
#define D5  587
#define Eb5 622
#define E5  660
#define F5  698
#define Fs5 740
#define G5  784
#define Ab5 831
#define A5  880
#define Bb5 932
#define B5  988

#endif /* NOTES_H_ */
