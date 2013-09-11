/***************************************************************************//**
 *   @file   UART.c
 *   @brief  Communication file
 *	 @date	 04.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

#include "../Header/GlobalDef.h"
#include "../Header/InputOutput.h"
#include <avr/io.h>

union Ubyte_def ButtonsFlags;    

void IO_Init(void)
{
  //For the heartbeat
  //DDRE = 0x04;
  //PORTE = 0x04;
  bfHeartbeatDir = C_OUT;
  bfHeartbeat    = C_LED_OFF;
  
  //For reading the buttons
  bfJoyButtonDir = C_IN;
  bfJoyButtonPull = C_ON;
  bfLeftButtonDir = C_IN;  
  bfRightButtonDir = C_IN;
  
}

void ReadButtons (void)
{  
  if ((bfPrevJoyButt == C_ON) &&(bfJoyButton == C_OFF))           
  {
    bfJoyButtFlag = C_ON;
  }
  bfPrevJoyButt = bfJoyButton;
  
  if ((bfPrevLeftButt == C_OFF) &&(bfLeftButton == C_ON))
  {
    bfLeftButtFlag = C_ON;
  }
  bfPrevLeftButt = bfLeftButton;
  
  if ((bfPrevRightButt == C_OFF) &&(bfRightButton == C_ON))
  {
    bfRightButtFlag = C_ON;
  }
  bfPrevRightButt = bfRightButton;
    
  //bfJoyButtFlag = bfJoyButton;
  //bfLeftButtFlag = bfLeftButton;
  //bfRightButtFlag = bfRightButton;
}