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

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
union Ubyte_def ButtonsFlags;    

/***************************************************************************//**
 * @brief   Initializes all in and outputs
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void IO_Init(void)
{
  //For the Music pin output
  pinMusicDir = C_OUT;
  pinMusic = C_OFF;

  //For the Music debug pin output
  pinDebugMusicDir = C_OUT;
  pinDebugMusic = C_OFF;

  //For the heartbeat
  pinHeartbeatDir = C_OUT;
  pinHeartbeat    = C_LED_OFF;
  
  //For reading the buttons
  pinJoyButtonDir = C_IN;
  pinJoyButtonPull = C_ON;
  pinLeftButtonDir = C_IN;  
  pinRightButtonDir = C_IN;
  
  //Enable external interrupts
  DDRE &= ~(1<<PE0);
  //Enable Pullup on interrupt pin
  PORTE |= (1<<PE0);
  //First it has to be cleared
  GICR &= ~(1 << INT2);
  //Clear ISC2 for enabling interrupt on falling edge
  EMCUCR &= ~(1 << ISC2);
  //Enable INT2
  GICR |= (1 << INT2);
}

/***************************************************************************//**
 * @brief 	Reads the values of the touch buttons on the Multifunction Card
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void Read_Buttons (void)
{  
  if ((bfPrevJoyButt == C_ON) &&(pinJoyButton == C_OFF))           
  {
    bfJoyButtFlag = C_ON;
  }
  bfPrevJoyButt = pinJoyButton;
  
  if ((bfPrevLeftButt == C_OFF) &&(pinLeftButton == C_ON))
  {
    bfLeftButtFlag = C_ON;
  }
  bfPrevLeftButt = pinLeftButton;
  
  if ((bfPrevRightButt == C_OFF) &&(pinRightButton == C_ON))
  {
    bfRightButtFlag = C_ON;
  }
  bfPrevRightButt = pinRightButton;   
}