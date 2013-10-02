/***************************************************************************//**
 *   @file   CAN.c
 *   @brief  CAN bus communication
 *	 @date	 01.10.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/CAN.h"
#include "../Header/MCP2515.h"

/***************************************************************************//**
 * @brief 	Initializes the CAN communication
 * @param   None
 * @return 	None
 * @date	  01.10.2013 
*******************************************************************************/
void Can_Init()
{
  MCP2515_Init();
  MCP2515_Change_Mode(MCP2515_LOOPBACK_MODE);
}
