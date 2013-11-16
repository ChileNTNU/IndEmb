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
#include "../Header/InputOutput.h"
#include "../Header/Music.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
volatile union Ubyte_def TimerFlags;
unsigned char Song_to_play;
unsigned char Note_to_play;

/***************************************************************************//**
 * @brief 	Initializes a 10 ms Timer.
 * @param   None.
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
void Timer_Init(void)
{  
  TIMSK = 0x00;                                 //Clear register and disable interrupts
  
  //Timer0 is for the frequency of the music tones
  TCCR0 = (1 << WGM01)                          //Clear Timer on Compare match (CTC) mode 
  //        |(1<<CS01)|(1<<CS00)                  //Set Clock 64 preescaler THE PREESCALER IS SET BY THE FUNCTION Play_Music()
          |(1<<COM00);			                    //For toggling the output on compare match 
  TIMSK &= ~(1 << OCIE0);                       //Disable compare interrupt  
  OCR0 = 109;											              //Selected value for music tone
  
  //Timer1 is for the length of the music tones
  TCCR1B = (1<<WGM12);                          //Clear Timer on Compare match (CTC) mode
  //         |(1<<CS12)|(1<<CS10);              //Set clock 1024 preescaler THE PREESCALER IS SET BY THE FUNCTION Play_Music() 
  TCCR1A = (1<<COM1A0);			                    //For toggling the output on compare match 
  TIMSK |= (1 << OCIE1A);                       //Enable compare interrupt
  OCR1A = 298;											            //Value for a 16Hz interrupt  
  
  //Timer2 is for the 10ms system tick
  TCCR2 = (1 << WGM21)|(1<<CS22)|(1<<CS21)|(1<<CS20);			//Clear Timer on Compare match (CTC) mode & Clock and 1024 preescaler
  TIMSK |= (1 << OCIE2);                                  //Enable compare interrupt
  OCR2 = 47;											                        //Value for 10ms Interrupt
  //TIFR = (1 << OCF0);      
}

/***************************************************************************//**
 * @brief 	ISR of the timer2. Used to generate 10ms, 100ms and 1s flags
 * @param   None.
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
ISR(TIMER2_COMP_vect)
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

/***************************************************************************//**
 * @brief 	ISR of the timer1. Used to generate 16Hz interrupt for the game music
 * @param   None.
 * @return 	None.
 * @date	  13.11.2013 
*******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
  static unsigned char Length_to_play = 0;
  MusicNote * Pointer_to_song;
  unsigned int Address;  
  unsigned char Max_length;
  unsigned char Note_Index; 
  unsigned char Value_of_note;     
  
  Pointer_to_song = (MusicNote *) pgm_read_word(&Songs[Song_to_play]);  
  Address = (unsigned int)&Pointer_to_song[Note_to_play];
  //Value_of_note = (unsigned char)pgm_read_byte(&Pointer_to_song[Note_to_play]);  
  //Max_length =(unsigned char)pgm_read_byte(((unsigned int)&Pointer_to_song[Note_to_play]) + 1);
  Note_Index = (unsigned char)pgm_read_byte(Address);  
  Max_length =(unsigned char)pgm_read_byte(Address + 1);
  
  if (Max_length == 0)
  {
    Note_to_play = 0;
    Length_to_play = 0;
  }  
  else if ((Max_length - 1) == Length_to_play)  
  {
    Note_to_play++;
    Length_to_play = 0;
  }
  else
  {
    Length_to_play++;  
  }
  
  //Read the corresponding value for each note
  Value_of_note = pgm_read_byte(&Tones[Note_Index]);  
  OCR0 = Value_of_note;  
}
