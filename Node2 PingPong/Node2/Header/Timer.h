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

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define bf10msFlag              TimerFlags.Ubit.b0      // 10ms flag
#define bf100msFlag             TimerFlags.Ubit.b1      // 100ms flag
#define bf1sFlag                TimerFlags.Ubit.b2      // 1 sec flag

//Macros for PWM
#define CMP_MAX2_1MS            (65)    //Maximum value for 2.1 ms 
#define CMP_MIN0_9MS            (29)    //Minimum value for 0.9 ms 
#define CMP_TIMER_PWM           (624)   //Value that the timer has to count for having a period of 20ms sharp

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Timer_Init(void);

#endif /* TIMER_H_ */