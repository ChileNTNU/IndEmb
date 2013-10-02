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
#include "../Header/UART.h"

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
 * @brief 	Loads a transmission buffer on the MCP2515
 * @param   Buffer_to_send   Selects to which buffer the data should be written
 * @param   Data_to_send     Data which is going to be send
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Load_Tx_Buffer(unsigned char Buffer_to_send, unsigned char Data_to_send)
{
  pinSSmcp2515 = C_SS_ENABLE;
  SPI_put_char(Buffer_to_send);
  SPI_put_char(Data_to_send);
  pinSSmcp2515 = C_SS_DISABLE;
}

/***************************************************************************//**
 * @brief 	Request to the MCP2515 to send data over the CAN bus
 * @param   Buffer_to_send   Selects which buffer is sent over the CAN bus
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Request_to_Send(unsigned char Buffer_to_send)
{
  pinSSmcp2515 = C_SS_ENABLE;
  SPI_put_char(Buffer_to_send); 
  pinSSmcp2515 = C_SS_DISABLE;
}

/***************************************************************************//**
 * @brief 	Reads the RX buffer from CAN controller
 * @param   Cmd_Read_Rx_Buffer    Sets the command for reading from a specific Rx buffer
 * @return 	SPIRxData  Sends back the read data 
 * @date	  30.09.2013 
*******************************************************************************/
unsigned char MCP2515_Read_Rx_Buffer(unsigned char Cmd_Read_Rx_Buffer)
{            
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(Cmd_Read_Rx_Buffer); 
  SPI_put_char(DUMMY);
  pinSSmcp2515 = C_SS_DISABLE; 
  return SPIRxData;  
}

/***************************************************************************//**
 * @brief 	Reads the status register of the MCP2515
 * @param   None
 * @return 	SPIRxData  Sends back the read data 
 * @date	  01.10.2013 
*******************************************************************************/
unsigned char MCP2515_Read_Status(void)
{            
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(READ_STATUS); 
  SPI_put_char(DUMMY);
  SPI_put_char(DUMMY);
  pinSSmcp2515 = C_SS_DISABLE; 
  return SPIRxData;  
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
  
  i = MCP2515_Read(MCP_CANSTAT);
  i = i & 0xE0;
  if (i != 0x80)
  {
    printf("MCP2515 not in configuration mode\n");
  }
}

/***************************************************************************//**
 * @brief 	Initializes the MCP2515 module
 * @param   None.
 * @return 	None.
 * @date	  30.09.2013 
*******************************************************************************/
char MCP2515_Change_Mode (unsigned char MCP2515_Mode)
{
  MCP2515_Bit_Modify(MCP_CANCTRL,0xE0,MCP2515_Mode);
  if((MCP2515_Read(MCP_CANSTAT) & 0xE0) != MCP2515_Mode)
  {
    return C_ERROR;
  }
  else return C_SUCCESS;
}