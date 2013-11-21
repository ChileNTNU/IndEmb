/***************************************************************************//**
 *   @file   ADC.c
 *   @brief  Implements functions to get the position of the slider and the
 *            joystick of the USB-Multifunction Card
 *	 @date	 04.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/ADC.h"
#include "../Header/GlobalDef.h"
#include <avr/interrupt.h>

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
volatile unsigned char ADC_goal;
union Ubyte_def ADCFlags;

/***************************************************************************//**
 * @brief 	Initializes the internal ADC module
 * @param   None
 * @return 	None
 * @date	  21.10.2013 
*******************************************************************************/
void ADC_Init(void)
{
  ADMUX |= (1<<ADLAR) | (1<<REFS0);     //Set the ADC left adjust and Analog reference to 5V Vdd and not AVdd
  ADCSRA |= (1<<ADEN) | (1<<ADIE);      //Enable ADC and ADC interrupt
  
  ADC_goal = 0xFF;       //Initializing the ADC goal variable as if it has read 5V
  ADCallFlags = 0x00;    //Initializing all flags to zero
} 

/***************************************************************************//**
 * @brief 	Start a ADC conversion
 * @param   None
 * @return 	None
 * @date	  21.10.2013 
*******************************************************************************/
void ADC_Start_Conversion(void)
{
  bfADCstart = C_ON;
} 

/***************************************************************************//**
 * @brief 	Detects if a goal has been scored
 * @param   None
 * @return 	None
 * @date	  23.10.2013 
*******************************************************************************/
void Detect_Goal(void)
{
  if (ADC_goal < GOAL_THRESHOLD)
  {
    if (bfPrevGoalFlag == C_OFF)
    {
      bfGoalFlag = C_ON;      
    }   
    bfPrevGoalFlag = C_ON;
  }
  else
  {
   bfPrevGoalFlag = C_OFF;    
  }  
} 

/***************************************************************************//**
 * @brief 	ISR for reading the ADC
 * @param   None.
 * @return 	None.
 * @date	  021.10.2013 
*******************************************************************************/
ISR(ADC_vect)
{      
  //First get the 15/16 proportion of the old ADC value
  //First get the 7/8 proportion of the old ADC value
  ADC_goal = ADC_goal - (ADC_goal >> 2);
  //Get the other 16th from the new ADC value and add them.
  //Get the other 8th from the new ADC value and add them.
  ADC_goal = ADC_goal + (ADCH >> 3); 
}