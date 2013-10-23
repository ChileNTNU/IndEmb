/***************************************************************************//**
 *   @file   InputOutput.c
 *   @brief  Implements functions to read the touch buttons and the joystick
 *            button from the USB Multifunction card
 *	 @date	 12.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include "../Header/GlobalDef.h"
#include "../Header/InputOutput.h"
#include "../Header/Timer.h"

/***************************************************************************//**
 * @brief   Initializes all in and outputs
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void IO_Init(void)
{
  //For the heartbeat
  pinHeartbeatDir = C_OUT;
  pinHeartbeat    = C_LED_OFF;
  
  //For reading the buttons
//  pinJoyButtonDir = C_IN;
//  pinJoyButtonPull = C_ON;
//  pinLeftButtonDir = C_IN;  
//  pinRightButtonDir = C_IN;

/*
Set pins for I2C

*/
  
  //Set pin for ADC as input
  DDRF  &= ~(1<<PF0);
    
  //Setting pin for PWM
  DDRB  |= (1<<PB5);
  
  //Setting pin for receiving the interrupt from the CAN controller
  //Setting PD2 as input
  DDRD &= ~(1<<PD2);
  //Enable Pullup on interrupt pin
  PORTD |= (1<<PD2);
  //Enable interrupt on falling edge
  EICRA |= (1 << ISC21);
  //Enable INT2
  EIMSK |= (1 << INT2);
}

/***************************************************************************//**
 * @brief   Refreshes the PWM compare value depending on Joystick position
 * @param   Message   This is the CAN message coming from Node 1 which contains the Direction of the Joystick
 * @return 	None.
 * @date	  21.10.2013 
*******************************************************************************/
void Servo_Position (CANStruct * Message)
{
  switch (Message->data[0])
    {
    case Left:
      OCR1A = CMP_MAX_2_1MS;      //Accessing the 16 bit register in just one instruction, instead of High and Low  
	    break;
    case Right:
      OCR1A = CMP_MIN_0_9MS;  
      break;
    case Neutral:
      OCR1A = CMP_1_5MS;
      break;
    default:
      OCR1A = CMP_1_5MS;
      break;
    }  
}
