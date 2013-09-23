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

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
//extern union Ubyte_def ButtonsFlags;

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
//#define bfJoyButtFlag           ButtonsFlags.Ubit.b0      // Flag for Joystick button

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
//#define bfJoyButtonDir   REGISTER_BIT(DDRB,1)


/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void MoveSelection (struct MenuStruct *ptrMenu, struct JoyStruct *ptrJoystick);
void ChangeMenu (struct MenuStruct *ptrMenu);

#endif /* USERINTERFACE_H_ */