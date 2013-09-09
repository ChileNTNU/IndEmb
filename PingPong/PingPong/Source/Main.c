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
#include <stdio.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  struct JoyStruct Joystick_main;
  struct SlideStruct Sliders;
  
  DDRB = 0x02;
  PORTB = 0x02;
  
  UART_Init();
  ExMem_Init();  
  Timer_Init();
  fdevopen(UART_put_char, NULL);  
    
  EnableInterrupts();
  
  printf("--- Hola ---\r\n");
  SRAM_test();
  
  CalibrateJoystick(&Joystick_main) ;
  
  while(1)
  {
    if(bf100msFlag == C_ON)
    {
      bf100msFlag = C_OFF;
      PORTB ^= (1<<PB1);
      
      /*
      ADC_array[0]= ADC_Read(ADC_CH1);
      ADC_array[1]= ADC_Read(ADC_CH2);
      ADC_array[2]= ADC_Read(ADC_CH3);
      ADC_array[3]= ADC_Read(ADC_CH4);
      */
      ReadJoystick(&Joystick_main);
      ReadSliders(&Sliders);
      
      if(bf1sFlag == C_ON)
      {
        bf1sFlag = C_OFF;
        PrintJoystickPosition(&Joystick_main);
        PrintSlidersPosition(&Sliders);
      }
      
    }            
  }
  
  /*    
  data = ADC_Read(ADC_CH2);
  printf("ADC valuech2: %d\r\n",data);
*/      
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