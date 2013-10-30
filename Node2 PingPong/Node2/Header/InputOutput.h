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
/* Definitions                                                                */
/******************************************************************************/
#define MOTOR_RIGHT    (1)
#define MOTOR_LEFT     (0)

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
#define pinHeartbeatDir      REGISTER_BIT(DDRD,4)
#define pinHeartbeat         REGISTER_BIT(PORTD,4)

//---Outputs for the Motor box
//Reset active low to reset the encoder
#define pinResetEncoderDir   REGISTER_BIT(DDRA,6)
#define pinResetEncoder      REGISTER_BIT(PORTA,6)
//Active high to enable the Motor
#define pinEnableMotorDir    REGISTER_BIT(DDRA,4)
#define pinEnableMotor       REGISTER_BIT(PORTA,4)
//Active low to enable the encoder
#define pinOEencoderDir      REGISTER_BIT(DDRA,7)
#define pinOEencoder         REGISTER_BIT(PORTA,7)
//Low byte = High(5V)       High byte = Low(0V)
#define pinSelectLowEncDir   REGISTER_BIT(DDRA,5)
#define pinSelectLowEnc      REGISTER_BIT(PORTA,5)
//Right = High      Left = Low
#define pinDirMotorDir       REGISTER_BIT(DDRA,3)
#define pinDirMotor          REGISTER_BIT(PORTA,3)

//Inputs for the MotorBox
#define pinD0EncDir   REGISTER_BIT(DDRC,7)
#define pinD0Enc      REGISTER_BIT(PINC,7)
#define pinD0EncPull  REGISTER_BIT(PORTC,7)

#define pinD1EncDir   REGISTER_BIT(DDRC,6)
#define pinD1Enc      REGISTER_BIT(PINC,6)
#define pinD1EncPull  REGISTER_BIT(PORTC,6)

#define pinD2EncDir   REGISTER_BIT(DDRC,5)
#define pinD2Enc      REGISTER_BIT(PINC,5)
#define pinD2EncPull  REGISTER_BIT(PORTC,5)

#define pinD3EncDir   REGISTER_BIT(DDRC,4)
#define pinD3Enc      REGISTER_BIT(PINC,4)
#define pinD3EncPull  REGISTER_BIT(PORTC,4)

#define pinD4EncDir   REGISTER_BIT(DDRC,3)
#define pinD4Enc      REGISTER_BIT(PINC,3)
#define pinD4EncPull  REGISTER_BIT(PORTC,3)

#define pinD5EncDir   REGISTER_BIT(DDRC,2)
#define pinD5Enc      REGISTER_BIT(PINC,2)
#define pinD5EncPull  REGISTER_BIT(PORTC,2)

#define pinD6EncDir   REGISTER_BIT(DDRC,1)
#define pinD6Enc      REGISTER_BIT(PINC,1)
#define pinD6EncPull  REGISTER_BIT(PORTC,1)

#define pinD7EncDir   REGISTER_BIT(DDRC,0)
#define pinD7Enc      REGISTER_BIT(PINC,0)
#define pinD7EncPull  REGISTER_BIT(PORTC,0)

#define READ_PORTA   ((pinD7Enc<<7)| \
                      (pinD6Enc<<6)| \
                      (pinD5Enc<<5)| \
                      (pinD4Enc<<4)| \
                      (pinD3Enc<<3)| \
                      (pinD2Enc<<2)| \
                      (pinD1Enc<<1)| \
                      (pinD0Enc<<0))

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void IO_Init(void);
void Servo_Position(CANStruct * Message);
unsigned int Read_Encoder(void);
void Move_Motor(CANStruct * Message);
void Motor_Encoder_Init(unsigned int * max_encoder);

#endif /* INPUTOUTPUT_H_ */