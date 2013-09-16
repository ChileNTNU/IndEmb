/***************************************************************************//**
 *   @file   Timer.c
 *   @brief  Implements a 10ms Timer
 *	 @date	 09.09.2013
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
  OCR0 = 47;											              //Value for 10ms Interrupt
  //TIFR = (1 << OCF0);
    
}

ISR(TIMER0_COMP_vect)
{
  static unsigned char Prueba = 0;
  Prueba++;  
  bf10msFlag = C_ON;
  if((Prueba%10) == 0)
  {     
    bf100msFlag = C_ON;
  }
  if(Prueba == 100)      
  {
    Prueba = 0;
    bf1sFlag = C_ON;
  }
}