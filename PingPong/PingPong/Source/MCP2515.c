/***************************************************************************//**
 *   @file   MCP2515.c
 *   @brief  MCP2515 driver file
 *	 @date	 30.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/GlobalDef.h"
#include "../Header/SPI.h"
#include "../Header/MCP2515.h"

/***************************************************************************//**
 * @brief 	Resets the CAN controller
 * @param   None
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Reset(void)
{    
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(RESET);
  pinSSmcp2515 = C_SS_DISABLE; 
}

/***************************************************************************//**
 * @brief 	Reads from CAN controller
 * @param   Address    Sets the address from which we are going to read
 * @return 	SPIRxData  Sends back the read data 
 * @date	  30.09.2013 
*******************************************************************************/
unsigned char MCP2515_Read(unsigned char Address)
{            
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(READ);
  SPI_put_char(Address);
  SPI_put_char(DUMMY);
  pinSSmcp2515 = C_SS_DISABLE; 
  return SPIRxData;  
}

/***************************************************************************//**
 * @brief 	Writes to the CAN controller
 * @param   Address       Sets the address from which we are going to read
 * @param   Data_to_send  Data which is going to be send
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Write(unsigned char Address, unsigned char Data_to_send)
{    
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(WRITE);
  SPI_put_char(Address);
  SPI_put_char(Data_to_send);      
  pinSSmcp2515 = C_SS_DISABLE; 
}

/***************************************************************************//**
 * @brief 	Modifies a register from the CAN controller
 * @param   Address       Sets the address from which we are going to read
 * @param   Mask          Mask required for the bit to be modified 
 * @param   Data_to_send  Data which is going to be send
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Bit_Modify(unsigned char Address, unsigned char Mask, unsigned char Data_to_send)
{    
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(BIT_MODIFY);
  SPI_put_char(Address);
  SPI_put_char(Mask);
  SPI_put_char(Data_to_send);      
  pinSSmcp2515 = C_SS_DISABLE; 
}

/***************************************************************************//**
 * @brief 	Initializes the MCP2515 module
 * @param   None.
 * @return 	None.
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Init(void)
{  
  unsigned char i;
  MCP2515_Reset();
  
  // Wait for the MCP to start up
  for (i=0; i<128; i++ );
  
}
