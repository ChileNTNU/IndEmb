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
#include "../Header/GlobalDef.h"
#include <util/delay.h>
#include "../Header/UART.h"
#include <stdio.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  
  UART_Init();
  
  
  DDRB |= (1<<PB0);
  PORTB |= (1<<PB0);
  /*
  DDRE |= (1<<PE1);
  */
  
  fdevopen(UART_put_char, NULL);
    while(1)
    {
      UART_put_char(0xAA,NULL);
    }
    return 0;
}