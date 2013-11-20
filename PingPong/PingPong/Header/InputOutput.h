/***************************************************************************//**
 *   @file   InputOutput.h
 *   @brief  Header file to InputOutput.c
 *	 @date	 12.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/ 

#ifndef INPUTOUTPUT_H_
#define INPUTOUTPUT_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern union Ubyte_def ButtonsFlags;    

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define bfJoyButtFlag           ButtonsFlags.Ubit.b0      // Flag for Joystick button
#define bfLeftButtFlag          ButtonsFlags.Ubit.b1      // Flag for Left button
#define bfRightButtFlag         ButtonsFlags.Ubit.b2      // Flag for Right button
#define bfPrevJoyButt           ButtonsFlags.Ubit.b3      // Previous value for the Joystick button
#define bfPrevLeftButt          ButtonsFlags.Ubit.b4      // Previous value for the Left button
#define bfPrevRightButt         ButtonsFlags.Ubit.b5      // Previous value for the Right button

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
//Outputs
#define pinMusicDir       REGISTER_BIT(DDRB,0)
#define pinMusic          REGISTER_BIT(PORTB,0)

#define pinDebugMusicDir  REGISTER_BIT(DDRD,5)
#define pinDebugMusic     REGISTER_BIT(PORTD,5)

#define pinHeartbeatDir   REGISTER_BIT(DDRE,2)
#define pinHeartbeat      REGISTER_BIT(PORTE,2)

//Inputs
#define pinJoyButtonDir   REGISTER_BIT(DDRB,1)
#define pinJoyButton      REGISTER_BIT(PINB,1)
#define pinJoyButtonPull  REGISTER_BIT(PORTB,1)

#define pinLeftButtonDir  REGISTER_BIT(DDRB,2)
#define pinLeftButton     REGISTER_BIT(PINB,2)

#define pinRightButtonDir REGISTER_BIT(DDRB,3)
#define pinRightButton    REGISTER_BIT(PINB,3)

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void IO_Init(void);
void Read_Buttons(void);

#endif /* INPUTOUTPUT_H_ */