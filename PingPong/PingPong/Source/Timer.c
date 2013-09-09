/***************************************************************************//**
 *   @file   UART.c
 *   @brief  Communication file
 *	 @date	 04.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

#include "../Header/GlobalDef.h"
#include "../Header/Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile union Ubyte_def TimerFlags;

void Timer_Init(void)
{  
  TCCR0 = (1 << WGM01)|(1<<CS02)|(1<<CS00);			//Clear Timer on Compare match (CTC) mode & Clock and 1024 preescaler
  TIMSK |= (1 << OCIE0);                        //Enable compare interrupt
  OCR0 = 239;											              //Value for 50ms Interrupt
  //TIFR = (1 << OCF0);
    
}

ISR(TIMER0_COMP_vect)
{
  static unsigned char Prueba = 0;
  Prueba++;  
  if((Prueba%2) == 0 )
  {     
    bf100msFlag = C_ON;
  }
  if(Prueba == 20)      
  {
    Prueba = 0;
    bf1sFlag = C_ON;
  }
}