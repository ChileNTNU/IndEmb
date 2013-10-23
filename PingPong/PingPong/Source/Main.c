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
#include "../Header/CAN.h"
#include <stdio.h>
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  //unsigned char a,b;
  
  JoyStruct Joystick_main;
  struct SlideStruct Sliders;
  struct MenuStruct Menu;
  Menu.Menu_to_print = 0;
  Menu.SelectedMenu = 1;  
  
  CANStruct CAN_message_send = 
  { 0x01A0,
    4,
    {'A','B','C','D','0', '0', '0', '0'}
  };  
  //CAN_message_send.data[0] = 'A';
  CANStruct CAN_message_receive = 
  { .id = 0x0000,
    .length = 0
  };
    
  UART_Init();
  ExMem_Init();  
  Timer_Init();
  IO_Init();
  Oled_Init();
  Oled_home();
  SPI_Init();  
  fdevopen(UART_put_char, NULL);  
    
  EnableInterrupts();
  
  printf("--- Hola ---\r\n");
  SRAM_test();
  SRAM_Clean();
  if (Can_Init() == C_ERROR)
  {
    printf("¡MCP2515 not in configuration mode!");
  }
  
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
      Read_Joystick(&Joystick_main);
      Read_Sliders(&Sliders);
      Move_Selection(&Menu, &Joystick_main);
      //Oled_Refresh(&Menu);                   //Refreshing the OLED from the RAM memory of the microcontroller
        
      //Define actions depending on which menu the user is
      switch (Menu.Menu_to_print)
      {
        case MAIN_MENU_ID:
          SRAM_Refresh_Menu(&Menu);
          break;
        case PLAY_MENU_ID:
          SRAM_Refresh_Menu(&Menu);
          break;
        case CONFIG_MENU_ID:
          SRAM_Refresh_Menu(&Menu);
          break;
        case HIGHSCORE_MENU_ID:
          //Different SRAM_Refresh_Menu(&Menu);
          SRAM_Refresh_Menu(&Menu);
          break;
        case GAME_ON_MENU_ID:
          //Different SRAM_Refresh_Menu(&Menu);
          SRAM_Refresh_Menu(&Menu);
          //On this menu you need to move Servo depending on the joystick
          //Builds the CAN message with the joystick data
          Can_Message_Joystick(&CAN_message_send, &Joystick_main);          
          Can_Messsage_Send(&CAN_message_send,BUFFER_0);
          //On this menu you need to read if it has scored a goal
          //Checks which interrupt occurred on the CAN controller
          Can_Interrupt_Vect();
          //Receives a message if an interrupt has occurred
          Can_Reception(&CAN_message_receive);
          
          //TODO Read goals from the CAN message received     
          break;
        default:
          break;
      }
        //This is just for normal menus
        //SRAM_Refresh_Menu(&Menu);
        
        Oled_Refresh_From_SRAM();                         
    }
    
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;      
      pinHeartbeat = ~pinHeartbeat;                  
      if (bfJoyButtFlag == C_ON)
      {
        bfJoyButtFlag = C_OFF;
        //Print_Joystick_Position(&Joystick_main);      //Commented because it has printf
        Change_Menu (&Menu);
      }
      
      if (bfLeftButtFlag == C_ON)
      {
        bfLeftButtFlag = C_OFF;
        //Print_Sliders_Position(&Sliders);            //Commented because it has printf
        //Oled display clean        
        Oled_Clear_Screen();
        //Can_Print_Message(&CAN_message_receive);     //Commented because it has printf
      }
      
      if (bfRightButtFlag == C_ON)
      {
        bfRightButtFlag = C_OFF;        
        //PrintSlidersPosition(&Sliders);                                       
        Can_Messsage_Send(&CAN_message_send,BUFFER_0);                                        
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