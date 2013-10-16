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

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
union Ubyte_def CANFlags;
volatile unsigned char CAN_Event;

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
 * @brief 	Loads the ID(16 bits), EID8, EID0 and DLC (data length) to a transmission buffer on the MCP2515
 * @param   Buffer_to_send   Selects to which buffer the data should be written
 * @param   Message_to_send  Pointer to CANStruct message
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Load_Tx_Buffer_Header(unsigned char Buffer_to_send, CANStruct * Message_to_send )
{
  unsigned char Low_byte;
  unsigned char High_byte;
  pinSSmcp2515 = C_SS_ENABLE;
  SPI_put_char(Buffer_to_send);
  Low_byte = (unsigned char) Message_to_send->id;
  High_byte = (unsigned char) ( (Message_to_send->id) >> 8);  
  //Send ID
  SPI_put_char(High_byte);
  SPI_put_char(Low_byte);    
  //Send EID8
  SPI_put_char(0x00);
  //Send EID0
  SPI_put_char(0x00);
  //Send the length
  SPI_put_char(Message_to_send->length);    
  pinSSmcp2515 = C_SS_DISABLE;
}

/***************************************************************************//**
 * @brief 	Loads the Data (up to 8 bytes) to a transmission buffer on the MCP2515
 * @param   Buffer_to_send   Selects to which buffer the data should be written
 * @param   Message_to_send  Pointer to CANStruct message
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Load_Tx_Buffer_Data(unsigned char Buffer_to_send, CANStruct * Message_to_send)
{
  unsigned char a;
  pinSSmcp2515 = C_SS_ENABLE;
  //Send the command
  SPI_put_char(Buffer_to_send);
  //Send the data
  for (a = 0; a < Message_to_send->length; a++)
  {
    SPI_put_char(Message_to_send->data[a]);
  }  
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
 * @brief 	Receives the ID(16 bits), EID8, EID0 and DLC(data length) from a reception buffer on the MCP2515
 * @param   Buffer_to_send   Selects to which buffer the data should be written
 * @param   Message_to_send  Pointer to CANStruct message
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Read_Rx_Buffer_Header(unsigned char Cmd_Read_Rx_Buffer, CANStruct * Message_received)
{                
  unsigned int dummy;
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(Cmd_Read_Rx_Buffer); 
  //Read higher byte of the ID
  SPI_put_char(DUMMY);
  dummy = (unsigned int) SPIRxData ;
  dummy = dummy << 8;
  //Read lower byte of the ID
  SPI_put_char(DUMMY);
  dummy = dummy | (unsigned int) SPIRxData;
  Message_received->id = dummy;  
  //Read EID8
  SPI_put_char(DUMMY);
  //Read EID0
  SPI_put_char(DUMMY);
  //Read data length
  SPI_put_char(DUMMY);
  Message_received->length = SPIRxData;
  pinSSmcp2515 = C_SS_DISABLE; 
}

/***************************************************************************//**
 * @brief 	Receives the Data(up to 8 bytes) from a reception buffer on the MCP2515
 * @param   Buffer_to_send   Selects to which buffer the data should be written
 * @param   Message_to_send  Pointer to CANStruct message
 * @return 	None
 * @date	  30.09.2013 
*******************************************************************************/
void MCP2515_Read_Rx_Buffer_Data(unsigned char Cmd_Read_Rx_Buffer, CANStruct * Message_received)
{              
  unsigned int a;  
  pinSSmcp2515 = C_SS_ENABLE; 
  SPI_put_char(Cmd_Read_Rx_Buffer); 
  //Read the data depending on the length
  for (a = 0; a < Message_received->length; a++)
  {
    SPI_put_char(DUMMY);
    Message_received->data[a] = SPIRxData;
  }
  pinSSmcp2515 = C_SS_DISABLE; 
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
 * @return 	State    Indicates if the module could be initialized.
 * @date	  30.09.2013 
*******************************************************************************/
char MCP2515_Init(void)
{  
  unsigned char i;
  
  //Setting interrupt flags to zero
  CANintFlags = 0x00;
  
  MCP2515_Reset();
  
  // Wait for the MCP to start up
  for (i=0; i<128; i++ );
  
  //Enable transmission and reception interrupts
  //MCP2515_Bit_Modify(MCP_CANINTE,0x1F,0x1F);  
  
  //Enable just reception interrupts (Buffer 0 and 1)
  //MCP2515_Bit_Modify(MCP_CANINTE,0xFF,0x03);
   
  //Enable just reception interrupts (Buffer 0)
  MCP2515_Bit_Modify(MCP_CANINTE,0xFF,0x01);
  
  i = MCP2515_Read(MCP_CANSTAT);
  i = i & 0xE0;
  if (i != 0x80)
  {
    //The mode was not Configuration mode
    return C_ERROR;
  }
  else return C_SUCCESS;
}

/***************************************************************************//**
 * @brief 	Changes the mode of the CAN controller
 * @param   MCP2515_Mode    The desired mode to be selected
 * @return 	State           Indicates if the mode could be changed
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

/***************************************************************************//**
 * @brief 	ISR for detecting an event on the CAN controller
 * @param   None.
 * @return 	None.
 * @date	  09.10.2013 
*******************************************************************************/
ISR(INT2_vect)
{      
  CAN_Event = 0xFF;
  //-----------------------------------------------------------------------------
  //It is not possible to read the INTFLAGS during the interruption service routine
  //-----------------------------------------------------------------------------
  //CANintFlags = MCP2515_Read_Status(); 
}