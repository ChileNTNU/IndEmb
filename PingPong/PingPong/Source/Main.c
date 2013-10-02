/***************************************************************************//**
 *   @file   main.c
 *   @brief  This is the main file for the PingPong project
 *	 @date	 27.08.2013
 *   @author Tobias Franzen and Emilio Garcia
********************************************************************************
 * - Controller:	AVR ATMEGA162
 * - IDE:			ATMEL Studio 6
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/GlobalDef.h"
#include <util/delay.h>
#include "../Header/UART.h"
#include "../Header/SRAM.h"
#include "../Header/ADC.h"
#include "../Header/Timer.h"
#include "../Header/InputOutput.h"
#include "../Header/Oled.h"
#include "../Header/font_5x7.h"
#include "../Header/Menus.h"
#include "../Header/UserInterface.h"
#include "../Header/SPI.h"
#include "../Header/MCP2515.h"
#include <stdio.h>
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  unsigned char a;
  
  struct JoyStruct Joystick_main;
  struct SlideStruct Sliders;
  struct MenuStruct Menu;
  Menu.Menu_to_print = 0;
  Menu.SelectedMenu = 1;        
    
  UART_Init();
  ExMem_Init();  
  Timer_Init();
  IO_Init();
  Oled_Init();
  Oled_home();
  SPI_Init();  
  fdevopen(UART_put_char, NULL);  
    
  EnableInterrupts();
  
  //printf("--- Hola ---\r\n");
  SRAM_test();
  SRAM_Clean();
  MCP2515_Init();
  
  Calibrate_Joystick(&Joystick_main) ;
  
  while(1)
  {    
    if (bf10msFlag == C_ON)
    {
      bf10msFlag = C_OFF;
      Read_Buttons();      
    }
    
    if(bf100msFlag == C_ON)
    {
      bf100msFlag = C_OFF;
      pinHeartbeat = ~pinHeartbeat;      
      Read_Joystick(&Joystick_main);
      Read_Sliders(&Sliders);                  
      Move_Selection(&Menu, &Joystick_main);
      //Oled_Refresh(&Menu);
      SRAM_Refresh_Menu(&Menu);
      Oled_Refresh_From_SRAM();
    }
    
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;                  
                  
      if (bfJoyButtFlag == C_ON)
      {
        bfJoyButtFlag = C_OFF;
        Print_Joystick_Position(&Joystick_main);
        Change_Menu (&Menu);
      }
      
      if (bfLeftButtFlag == C_ON)
      {
        bfLeftButtFlag = C_OFF;
        Print_Sliders_Position(&Sliders);
        //Oled display clean        
        Oled_Clear_Screen();
      }
      
      if (bfRightButtFlag == C_ON)
      {
        bfRightButtFlag = C_OFF;        
        //PrintSlidersPosition(&Sliders);
        //Read previous value of Stat bits
        a = MCP2515_Read(MCP_CANSTAT);        
        UART_put_char(0x01, NULL);
        UART_put_char(a, NULL);
        //Change to Loopback mode
        //MCP2515_Bit_Modify(MCP_CANCTRL,0xE0,0x40);
        MCP2515_Change_Mode(MCP2515_LOOPBACK_MODE);        
        a = MCP2515_Read(MCP_CANSTAT);
        UART_put_char(0x02, NULL);
        UART_put_char(a, NULL);        
        //MCP2515_Write(MCP_CANCTRL,0x1F);
        //MCP2515_Bit_Modify(MCP_CANINTE,0x01,0x01);
        //Clear tx flag for buffer 0                        
        MCP2515_Bit_Modify(MCP_TXB0CTRL,0x08,0x00);        
        a = MCP2515_Read(MCP_TXB0CTRL);
        UART_put_char(0x03, NULL);
        UART_put_char(a, NULL);
        //Set data to send
        MCP2515_Load_Tx_Buffer(LOAD_BUFFER_0_ID,0xA0);
        a = MCP2515_Read(0x31);
        UART_put_char(0x04, NULL);
        UART_put_char(a, NULL);
        
        //MCP2515_Bit_Modify(MCP_TXB0CTRL,0x08,0x08);
        MCP2515_Request_to_Send(RTS_TX_BUFFER_0);
        
        a = 0x00;
        while (a != 0x01)
        {
          //a = MCP2515_Read(MCP_CANINTF);
          a = MCP2515_Read_Status();
          a = a & 0x01;
        }
        
        //for (a=0; a<128; a++ );
        a = MCP2515_Read(MCP_TXB0CTRL);
        UART_put_char(0x05, NULL);
        UART_put_char(a, NULL);
        
        a = MCP2515_Read_Rx_Buffer(READ_BUFFER_0_ID);
        UART_put_char(0x06, NULL);
        UART_put_char(a, NULL);
        
      }                  
    }
  }
        
  return 0;
  
  /*
  while(1)
  {        	  
    if (RxData == 0x41)
    {
      PORTA = ~PORTA;
      RxData = 0x00;
    }        
  }
  */  
}