/***************************************************************************//**
 *   @file   main.c
 *   @brief  This is the main file for the PingPong project Node 2
 *	 @date	 14.10.2013
 *   @author Tobias Franzen and Emilio Garcia
********************************************************************************
 * - Controller:	AVR ATMEGA128
 * - IDE:			ATMEL Studio 6.1
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "../Header/GlobalDef.h" //Should be before util/delay.h
#include <util/delay.h>
#include "../Header/UART.h"
#include "../Header/Timer.h"
#include "../Header/SPI.h"
#include "../Header/MCP2515.h"
#include "../Header/CAN.h"
#include "../Header/InputOutput.h"
#include "../Header/ADC.h"

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  //unsigned char a;
  
  CANStruct CAN_message_send =
  /*
  { 0x41AF,
    6,
    {'A','B','C','D','E', 'F', '0', '0'}
  };
  */
  { 0x41AF,
    0,
    {0,0,0,0,0,0,0,0}
  };
  //CAN_message_send.data[0] = 'A';
  CANStruct CAN_message_receive =
  { .id = 0x0000,
    .length = 0
  };

  
  UART_Init();
  fdevopen(UART_put_char, NULL);  
  SPI_Init();  
  IO_Init();
  Timer_Init();
  ADC_Init();
  EnableInterrupts();
  if (Can_Init() == C_ERROR)
  {
    printf("�MCP2515 not in configuration mode!");
  }
    
  while(1)
  {
    if (bf10msFlag == C_ON)
    {
      bf10msFlag = C_OFF;
      //PORTD ^= (1<<PD0);    //For toggling PD0 pin      
    }
    
    if(bf100msFlag == C_ON)
    {
      bf100msFlag = C_OFF;
      //CAN sending activities
      Can_Clear_Message(&CAN_message_send);
      Can_Build_Message (&CAN_message_send);
      if (CAN_message_send.length != 0)
      {
        Can_Messsage_Send(&CAN_message_send,BUFFER_0);
      }
      //----------------------
      //CAN Receiving activities
      Can_Interrupt_Vect();
      Can_Reception(&CAN_message_receive);      
      //----------------------
      Servo_Position(&CAN_message_receive);
      ADC_Start_Conversion();
    }  
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;
      pinHeartbeat = ~pinHeartbeat;
      Detect_Goal();
      //Can_Print_Message(&CAN_message_receive);
      UART_put_char(ADC_goal,NULL);      
    }
  }
  return 0;
}