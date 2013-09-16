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
//#include "../Header/font_5x7.h"
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
    
  UART_Init();
  ExMem_Init();  
  Timer_Init();
  IO_Init();
  Oled_Init();
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
    }
    
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;      
      
      if (bfJoyButtFlag == C_ON)
      {
        bfJoyButtFlag = C_OFF;
        PrintJoystickPosition(&Joystick_main);
        write_c(0xAE); // display off
      }
      
      if (bfLeftButtFlag == C_ON)
      {
        bfLeftButtFlag = C_OFF;
        PrintSlidersPosition(&Sliders);
        Oled_clear_screen();
      }
      
      if (bfRightButtFlag == C_ON)
      {
        bfRightButtFlag = C_OFF;        
        PrintSlidersPosition(&Sliders);
        /*
        //This is for horizontal addresing
        write_c(0X20);       
        write_c(0X00);
        //This is for setting the active colums. In this case from Col_0 to Col_127                        
        write_c(0x21);
        write_c(0x00);
        write_c(0x7F);
        //This is for setting the page to print. In this case from Page_0 to Page-7
        write_c(0x22);
        write_c(0x00);
        write_c(0x07);
        
        Oled_put_char('H');
        Oled_put_char('o');
        Oled_put_char('l');
        Oled_put_char('a');
        Oled_put_char('.');
        Oled_put_char('.');
        Oled_put_char('.');
        */
        Oled_home();        
        Oled_put_char('H');
        Oled_put_char('o');
        Oled_put_char('l');
        Oled_put_char('a');
        Oled_put_char('.');
        Oled_put_char('.');
        Oled_put_char('.');
        Oled_goto_line(1);
        Oled_put_char('B');
        Oled_put_char('O');
        Oled_put_char('L');
        Oled_put_char('A');
        Oled_put_char('-');
        Oled_put_char('-');
        Oled_put_char('-');
        Oled_pos(2,5);
        Oled_put_char('V');
        Oled_put_char('a');
        Oled_put_char('t');
        Oled_put_char('o');
        Oled_put_char('!');
        Oled_put_char('!');
        Oled_put_char('!');
        
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