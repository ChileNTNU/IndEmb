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
#include "../Header/InputOutput.h"
#include "../Header/UART.h"

/***************************************************************************//**
 * @brief 	Initializes the CAN communication
 * @param   None
 * @return 	None
 * @date	  01.10.2013 
*******************************************************************************/
char Can_Init(void)
{
  
  if (MCP2515_Init() == C_ERROR)
  {
    return C_ERROR;
  }
  
  if(MCP2515_Change_Mode(MCP2515_NORMAL_MODE) == C_ERROR)
  {
    return C_ERROR;    
  }
  
  return C_SUCCESS;
  
}

/***************************************************************************//**
 * @brief 	Sends a CAN message
 * @param   Message_to_send  This is the CAN message which will be sent
 * @param   Buffer_num       Selects the transmission buffer
 * @return 	State            Indicates if the message could be sent
 * @date	  09.10.2013 
*******************************************************************************/
char Can_Messsage_Send(CANStruct * Message_to_send, char Buffer_num)
{  
  unsigned char Flag;
  unsigned char Buffer_Tx_register;
  unsigned char Buffer_Tx_ID;
  unsigned char Buffer_Tx_Data;
  unsigned char Buffer_Tx_RTS;
  
  //Select the addresses and the commands for each buffer
  switch (Buffer_num)
  {
    case 0:
        Buffer_Tx_register = MCP_TXB0CTRL;
        Buffer_Tx_ID = LOAD_BUFFER_0_ID;
        Buffer_Tx_Data = LOAD_BUFFER_0_DATA;
        Buffer_Tx_RTS = RTS_TX_BUFFER_0;    
        break;
    case 1:
        Buffer_Tx_register = MCP_TXB1CTRL;
        Buffer_Tx_ID = LOAD_BUFFER_1_ID;
        Buffer_Tx_Data = LOAD_BUFFER_1_DATA;
        Buffer_Tx_RTS = RTS_TX_BUFFER_1;
        break;
    case 2:
        Buffer_Tx_register = MCP_TXB2CTRL;
        Buffer_Tx_ID = LOAD_BUFFER_2_ID;
        Buffer_Tx_Data = LOAD_BUFFER_2_DATA;
        Buffer_Tx_RTS = RTS_TX_BUFFER_2;
        break;
    default:
        Buffer_Tx_register = MCP_TXB0CTRL;
        Buffer_Tx_ID = LOAD_BUFFER_0_ID;
        Buffer_Tx_Data = LOAD_BUFFER_0_DATA;
        Buffer_Tx_RTS = RTS_TX_BUFFER_0;
        break;        
  }
  //Read if the transmission flag is off.
  //If it is off it means you can put a message on the Tx buffer
  Flag = MCP2515_Read(Buffer_Tx_register);  
  Flag = Flag & MCP_TXREQ;
  if (Flag == MCP_TXREQ)
  {
    return C_ERROR;
  }  
  //Load the Header of the CAN message
  MCP2515_Load_Tx_Buffer_Header(Buffer_Tx_ID,Message_to_send);
  //Load the Data of the CAN message
  MCP2515_Load_Tx_Buffer_Data(Buffer_Tx_Data,Message_to_send);
  //Send a Request_to send in order to send the data
  MCP2515_Request_to_Send(Buffer_Tx_RTS);
  return C_SUCCESS;
}

/***************************************************************************//**
 * @brief 	Receives a CAN message
 * @param   Message_to_receive  This is the CAN message which will be received
 * @param   Buffer_num          Selects the transmission buffer
 * @return 	None
 * @date	  09.10.2013 
*******************************************************************************/
void Can_Messsage_Receive(CANStruct * Message_to_receive, char Buffer_num)
{    
  unsigned char Buffer_Rx_ID;
  unsigned char Buffer_Rx_Data;
  
  //Select the addresses and the commands for each buffer
  switch (Buffer_num)
  {
    case 0:        
        Buffer_Rx_ID = READ_BUFFER_0_ID;
        Buffer_Rx_Data = READ_BUFFER_0_DATA;        
        break;
    case 1:
        Buffer_Rx_ID = READ_BUFFER_1_ID;
        Buffer_Rx_Data = READ_BUFFER_1_DATA;
        break;
    default:
        Buffer_Rx_ID = READ_BUFFER_0_ID;
        Buffer_Rx_Data = READ_BUFFER_0_DATA;
        break;        
  }
  //Receives the Header of the CAN message
  MCP2515_Read_Rx_Buffer_Header(Buffer_Rx_ID,Message_to_receive);
  //Receives the Data of the CAN message
  MCP2515_Read_Rx_Buffer_Data(Buffer_Rx_Data,Message_to_receive);
}


/***************************************************************************//**
 * @brief 	Reads all the flags from the CAN interrupts
 * @param   Message_received    This is the CAN message which will be received
 * @return 	None
 * @date	  14.10.2013 
*******************************************************************************/
void Can_Reception(CANStruct * Message_received)
{      
  if (CANintFlags != 0x00)
  {
    if (bfRxInt0 == C_ON)
    {
      Can_Messsage_Receive(Message_received,BUFFER_0);      
      bfRxInt0 = C_OFF;
    }
    else if (bfRxInt1 == C_ON)
    {
      Can_Messsage_Receive(Message_received,BUFFER_1);
      bfRxInt1 = C_OFF;
    }   
  }    
}  

/***************************************************************************//**
 * @brief 	Prints a CAN message to UART
 * @param   Message_received    This is the CAN message which will be received
 * @return 	None
 * @date	  14.10.2013 
*******************************************************************************/
void Can_Print_Message(CANStruct * Message_received)
{
  int a  ;
  a = (unsigned char) (Message_received->id >> 8);
  UART_put_char(a, NULL);
  UART_put_char((unsigned char)Message_received->id, NULL);
  UART_put_char(Message_received->length, NULL);
  UART_put_char(Message_received->data[0], NULL);
  UART_put_char(Message_received->data[1], NULL);
  UART_put_char(Message_received->data[2], NULL);
  UART_put_char(Message_received->data[3], NULL);
  UART_put_char(Message_received->data[4], NULL);
  UART_put_char(Message_received->data[5], NULL);
  UART_put_char(Message_received->data[6], NULL);
  UART_put_char(Message_received->data[7], NULL);
}

/***************************************************************************//**
 * @brief 	Build the CAN message that contains the Joystick data
 * @param   Message_to_send    This is the CAN message which will be sent
 * @param   JoyData            This is the structure containing the Joystick data
 * @return 	None
 * @date	  16.10.2013 
*******************************************************************************/
void Can_Message_Joystick(CANStruct * Message_to_send, JoyStruct * JoyData)
{
  Message_to_send->id = JOYSTICK_ID;
  Message_to_send->length = JOYSTICK_LENGTH;
  Message_to_send->data[0] = JoyData->Dir;
  Message_to_send->data[1] = (unsigned char)bfJoyButtFlag;
}

/***************************************************************************//**
 * @brief 	Reads the CAN interrupt flags in order to decide what to do
 * @param   None
 * @return 	None
 * @date	  14.10.2013 
*******************************************************************************/
void Can_Interrupt_Vect(void)
{
 if (CAN_Event != 0x00)
 {
   //Read the flags
   CANintFlags = MCP2515_Read(MCP_CANINTF);  
   //Erase the flags
   MCP2515_Bit_Modify(MCP_CANINTF,0xFF,0x00);
   //Clear CAN event flag
   CAN_Event = 0x00;
 }
}

/***************************************************************************//**
 * @brief 	Clear the CAN message
 * @param   Message     CAN message
 * @return 	None
 * @date	  23.10.2013 
*******************************************************************************/
void Can_Clear_Message(CANStruct * Message_to_clear)
{
  Message_to_clear->id = 0xFFFF;
  Message_to_clear->length = 0;
  Message_to_clear->data[0] = 0;
  Message_to_clear->data[1] = 0;
  Message_to_clear->data[2] = 0;
  Message_to_clear->data[3] = 0;
  Message_to_clear->data[4] = 0;
  Message_to_clear->data[5] = 0;
  Message_to_clear->data[6] = 0;
  Message_to_clear->data[7] = 0;
}
 
/*
void Can_Error();
void Can_Transmit_Complete();
void Can_Data_Receive();
*/