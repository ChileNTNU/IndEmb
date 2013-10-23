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

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
volatile union Ubyte_def TimerFlags;

/***************************************************************************//**
 * @brief 	Initializes two timers. One is a 10 ms Timer, and the other is for the PWM
 * @param   None.
 * @return 	None.
 * @date	  16.10.2013 
*******************************************************************************/
void Timer_Init(void)
{  
  //Initialization for the system tick
  TCCR0 = (1 << WGM01)|(1<<CS02)|(1<<CS01)|(1<<CS00);
                                                //Clear Timer on Compare match (CTC) mode & Clock and 1024 prescaler
                                                //IntOsc = 8MHz
  TIMSK |= (1 << OCIE0);                        //Enable compare interrupt
  OCR0 = 38;											              //Value for 10ms Interrupt
  
  //Initialization for the PWM. 
  //The servo needs a high output from 0.9ms to 2.1ms, with a 20ms period
  TCCR1A |= (1 << COM1A1);                      //Clear OC1A on compare match and set at Bottom
  TCCR1A |= (1 << WGM11);                       //Setting to a Fast PWM and a top count to ICR1
  TCCR1B |= (1 << WGM13) | (1 << WGM12);        //For setting this mode as well
  TCCR1B |= (1 << CS12);                        //Prescaler 256 so we can count until 20ms sharp
  
  //Values for the high time of the PWM
  OCR1AH = 0x00;
  OCR1AL = CMP_1_5MS;    
    
  //Set the top value for a 20ms period
  ICR1 = CMP_TIMER_PWM;  
}

/***************************************************************************//**
 * @brief 	ISR of the timer. Used to generate 10ms, 100ms and 1s flags. The interrupt is executed every 10 ms
 * @param   None.
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
ISR(TIMER0_COMP_vect)
{
  static unsigned char TimerCounter = 0;
  TimerCounter++;  
  bf10msFlag = C_ON;
  if((TimerCounter%10) == 0)
  {     
    bf100msFlag = C_ON;
  }
  if(TimerCounter == 100)      
  {
    TimerCounter = 0;
    bf1sFlag = C_ON;
  }
}