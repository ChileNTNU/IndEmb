/***************************************************************************//**
 *   @file   Timer.h
 *   @brief  Header file to Timer.c
 *	 @date	 09.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern volatile union Ubyte_def TimerFlags;
extern unsigned char Song_to_play;
extern unsigned char Note_to_play;

#define Play_Song(Selected_song) \
do \
{\
  TCCR0 |= (1<<CS01)|(1<<CS00);\
  TCCR1B |= (1<<CS12)|(1<<CS10);\
  Song_to_play = Selected_song;\
} while(0)


#define Stop_Music() \
do \
{\
  TCCR0 &= ~((1<<CS01)|(1<<CS00));\
  TCCR1B &= ~((1<<CS12)|(1<<CS10));\
  Note_to_play = 0;\
} while(0)

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define bf10msFlag              TimerFlags.Ubit.b0      // 10ms flag
#define bf100msFlag             TimerFlags.Ubit.b1      // 100ms flag
#define bf1sFlag                TimerFlags.Ubit.b2      // 1 sec flag
#define bfWriteEEPROM           TimerFlags.Ubit.b3      // Write EEPROM flag

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Timer_Init(void);

#endif /* TIMER_H_ */