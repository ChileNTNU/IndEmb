/***************************************************************************//**
 *   @file   Music.h
 *   @brief  Header file for the music
 *	 @date	 13.11.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef MUSIC_H_
#define MUSIC_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include <avr/pgmspace.h>

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/

typedef struct{
  char Tone;
  char Length;
} MusicNote;

#define PAUSE (0)  
#define C3    (1)  //DO
#define C3s   (2)
#define D3    (3)  //RE
#define D3s   (4)
#define E3    (5)  //MI
#define F3    (6)  //FA
#define F3s   (7)
#define G3    (8)  //SOL
#define G3s   (9)
#define A3    (10)  //LA
#define A3s   (11)  //LA
#define B3    (12)  //SI
#define C4    (13)  //DO at the middle of a piano
#define C4s   (14)  
#define D4    (15)  //RE
#define D4s   (16)  
#define E4    (17)  //MI
#define F4    (18)  //FA
#define F4s   (19)  
#define G4    (20)  //SOL
#define G4s   (21)
#define A4    (22)  //LA
#define A4s   (23)  //LA
#define B4    (24)  //SI
#define C5    (25)  //DO one higher octave
#define C5s   (26)  
#define D5    (27)  
#define D5s   (28)
#define E5    (29)
#define F5    (30)
#define F5s   (31)
#define G5    (32)
#define G5s   (33)
#define A5    (34)
#define A5s   (35)
#define B5    (36) 

#define TETRIS_SONG    (0)
#define MARIO_SONG     (1)
#define ENTE_SONG      (2)
#define CUCARACHA_SONG (3)

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern const MusicNote * const Songs[];
extern const char Tones[];

#endif /* MUSIC_H_ */