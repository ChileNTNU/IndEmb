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
#include "../Header/UART.h"

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
Set pin for PWM
Set pins for I2C
Set pin for ADC
*/
  
  //Setting PD2 as input
  DDRD &= ~(1<<PD2);
  //Enable Pullup on interrupt pin
  PORTD |= (1<<PD2);
  //Enable interrupt on falling edge
  EICRA |= (1 << ISC21);
  //Enable INT2
  EIMSK |= (1 << INT2);
}
