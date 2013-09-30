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

#include "../Header/GlobalDef.h"
#include "../Header/InputOutput.h"
#include <avr/io.h>

union Ubyte_def ButtonsFlags;    

/***************************************************************************//**
 * @brief   Initializes all in- and outputs
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void IO_Init(void)
{
  //For the heartbeat
  //DDRE = 0x04;
  //PORTE = 0x04;
  pinHeartbeatDir = C_OUT;
  pinHeartbeat    = C_LED_OFF;
  
  //For reading the buttons
  pinJoyButtonDir = C_IN;
  pinJoyButtonPull = C_ON;
  pinLeftButtonDir = C_IN;  
  pinRightButtonDir = C_IN;
  
}

/***************************************************************************//**
 * @brief 	Reads the values of the touch buttons on the Multifunction Card
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void ReadButtons (void)
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