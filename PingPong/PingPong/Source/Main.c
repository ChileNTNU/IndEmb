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

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{
  unsigned int a;
   
  //DDRA = 0x01;
  //PORTA = 0x01;
  
  UART_Init();  
  SRAM_Init();
  
  
  //UART_put_string("Hola\r\n");
  SRAM_test();

  //EnableInterrupts();
      
  return 0;
  
  /*
  while(1)
  {    
    
	  
    if (RxData == 0x41)
    {
      PORTA = ~PORTA;
      RxData = 0x00;
    }
    
    //LATCH_test();    
  }
  */  
}