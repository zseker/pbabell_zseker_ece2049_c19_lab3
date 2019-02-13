/*
 * ThroughTheFire.h
 *
 *  Created on: Jan 30, 2019
 *      Author: Phil
 */
#include "notes.h"

#ifndef THROUGHTHEFIRE_H_
#define THROUGHTHEFIRE_H_

#define BTN1 0x1
#define BTN2 0x2
#define BTN3 0x4
#define BTN4 0x8

struct note octaveScaleStruct[] = {{C4, 32, 0x1, 0},
                                   {D4, 32, 0x2, 0},
                                   {E4, 32, 0x4, 0},
                                   {F4, 32, 0x8, 0},
                                   {G4, 32, 0x1, 0},
                                   {A4, 32, 0x2, 0},
                                   {B4, 32, 0x4, 0},
                                   {C5, 32, 0x8, 0}};

struct note throughTheFire[] = {{Eb5, 16, BTN1},
                                {F5, 16, BTN2},
                                {G5, 16, BTN3},
                                {Eb5, 16, BTN4},

                                {F5, 16, BTN1},
                                {G5, 16, BTN2},
                                {Ab5, 16, BTN3},
                                {G5, 16, BTN4},

                                {Bb5, 16, 1},
                                {G5, 16, 1},
                                {Ab5, 16, 1},
                                {F5, 16, 1},

                                {G5, 16, 1},
                                {Eb5, 16, 1},
                                {F5, 16, 1},
                                {D5, 16, 1}};

struct note megalovania[] = {{D4, 2, 0},
                             {D4, 2, 0},
                             {D5, 4, 0},
                             {A4, 6, 0},
                             {Ab4, 4, 0},
                             {G4, 4, 0},
                             {F4, 4, 0},
                             {D4, 2, 0},
                             {F4, 2, 0},
                             {G4, 2, 0},

                             {C4, 2, 0},
                             {D4, 2, 0},
                             {D5, 4, 0},
                             {A4, 6, 0},
                             {Ab4, 4, 0},
                             {G4, 4, 0},
                             {F4, 4, 0},
                             {D4, 2, 0},
                             {F4, 2, 0},
                             {G4, 2, 0},

                             {B3, 2, 0},
                             {D4, 2, 0},
                             {D5, 4, 0},
                             {A4, 6, 0},
                             {Ab4, 4, 0},
                             {G4, 4, 0},
                             {F4, 4, 0},
                             {D4, 2, 0},
                             {F4, 2, 0},
                             {G4, 2, 0},

                             {F4, 4, 0},
                             {F4, 2, 0},
                             {F4, 4, 0},
                             {F4, 4, 0},
                             {F4, 4, 0},
                             {D4, 4, 0},
                             {D4, 6, 0},
                             {D4, 4, 0},
                             {F4, 2, 0},
                             {F4, 2, 0},
                             {F4, 2, 0},
                             {F4, 2, 0},
                             {F4, 4, 0},
                             {G4, 4, 0}};

struct note blue[] = {{A4, 16, BTN4, 0},

                      {Bb4, 8, BTN4, 0},
                      {D4, 8, BTN1, 0},
                      {G4, 8, BTN2, 0},
                      {Bb4, 8, BTN3, 0},

                      {C5, 8, BTN4, 0},
                      {F4, 8, BTN1, 0},
                      {A4, 8, BTN2, 0},
                      {Bb4, 16, BTN3, 0},

                      {G4, 8, BTN1, 0},
                      {Bb4, 8, BTN2, 0},
                      {D5, 8, BTN3, 0},

                      {Eb5, 8, BTN4, 0},
                      {G4, 8, BTN1, 0},
                      {D5, 8, BTN4, 0},
                      {C5, 8, BTN3, 0},

                      {Bb4, 8, BTN2, 0},
                      {D4, 8, BTN1, 0},
                      {G4, 8, BTN2, 0},
                      {Bb4, 8, BTN3, 0},

                      {C5, 8, BTN4, 0},
                      {F4, 8, BTN1, 0},
                      {A4, 8, BTN2, 0},
                      {Bb4, 16, BTN3, 0},

                      {G4, 8, BTN1, 0},
                      {Bb4, 8, BTN2, 0},
                      {D5, 8, BTN3, 0},

                      {Eb5, 8, BTN4, 0},
                      {G4, 8, BTN1, 0},
                      {D5, 8, BTN4, 0},
                      {C5, 8, BTN2, 0}};

#endif /* THROUGHTHEFIRE_H_ */
