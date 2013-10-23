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
#include "../Header/CAN.h"

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
/*
#define pinJoyButtonDir   REGISTER_BIT(DDRB,1)
#define pinJoyButton      REGISTER_BIT(PINB,1)
#define pinJoyButtonPull  REGISTER_BIT(PORTB,1)

#define pinLeftButtonDir  REGISTER_BIT(DDRB,2)
#define pinLeftButton     REGISTER_BIT(PINB,2)

#define pinRightButtonDir REGISTER_BIT(DDRB,3)
#define pinRightButton    REGISTER_BIT(PINB,3)
*/
#define pinHeartbeatDir   REGISTER_BIT(DDRD,4)
#define pinHeartbeat      REGISTER_BIT(PORTD,4)


/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void IO_Init(void);
void Servo_Position (CANStruct * Message);

#endif /* INPUTOUTPUT_H_ */