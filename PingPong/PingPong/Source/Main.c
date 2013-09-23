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
#include <stdio.h>
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
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
  fdevopen(UART_put_char, NULL);  
    
  EnableInterrupts();
  
  printf("--- Hola ---\r\n");
  SRAM_test();
  
  CalibrateJoystick(&Joystick_main) ;
  
  while(1)
  {    
    if (bf10msFlag == C_ON)
    {
      bf10msFlag = C_OFF;
      ReadButtons();
    }
    
    if(bf100msFlag == C_ON)
    {
      bf100msFlag = C_OFF;
      bfHeartbeat = ~bfHeartbeat;      
      ReadJoystick(&Joystick_main);
      ReadSliders(&Sliders);                  
      MoveSelection(&Menu, &Joystick_main);
    }
    
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;      
      
      Oled_Refresh(&Menu);
                  
      if (bfJoyButtFlag == C_ON)
      {
        bfJoyButtFlag = C_OFF;
        PrintJoystickPosition(&Joystick_main);
        ChangeMenu (&Menu);
      }
      
      if (bfLeftButtFlag == C_ON)
      {
        bfLeftButtFlag = C_OFF;
        PrintSlidersPosition(&Sliders);
        Oled_clear_screen(); //Oled display clean
      }
      
      if (bfRightButtFlag == C_ON)
      {
        bfRightButtFlag = C_OFF;        
        PrintSlidersPosition(&Sliders);                
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