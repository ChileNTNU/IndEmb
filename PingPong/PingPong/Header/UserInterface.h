/***************************************************************************//**
 *   @file   UserInterface.h
 *   @brief  Header file to UserInterface.c
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/CAN.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define Start_Timer(Timer) (((struct TimerStruct *)Timer)->Enable = C_ON) 
#define Stop_Timer(Timer) (((struct TimerStruct *)Timer)->Enable = C_OFF) 
/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Move_Selection(struct MenuStruct *ptrMenu, JoyStruct *ptrJoystick);
void Change_Menu(struct MenuStruct *ptrMenu);
void Check_Goals(CANStruct * Message, unsigned char * goals);
void Increase_Timer(struct TimerStruct * Timer);
void Reset_Timer(struct TimerStruct * Timer);

#endif /* USERINTERFACE_H_ */