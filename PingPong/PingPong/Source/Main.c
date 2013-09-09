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
#include "../Header/GlobalDef.h"
#include <util/delay.h>
#include "../Header/UART.h"
#include "../Header/SRAM.h"
#include <avr/interrupt.h>
#include "../Header/ADC.h"
#include <stdio.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{
  unsigned char data; 
  //DDRA = 0xFF;
  //PORTA = 0x10;
  
  UART_Init();  
  ExMem_Init();
  fdevopen(UART_put_char, NULL);    
  EnableInterrupts();
  
  printf("--- Hola ---\r\n");
  SRAM_test();  
  
  data = ADC_Read(ADC_CH1);
  printf("ADC value ch1: %d\r\n",data);
  
  data = ADC_Read(ADC_CH2);
  printf("ADC valuech2: %d\r\n",data);
      
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