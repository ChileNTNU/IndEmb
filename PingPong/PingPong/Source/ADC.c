/***************************************************************************//**
 *   @file   UART.c
 *   @brief  Communication file
 *	 @date	 04.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/


#include "../Header/ADC.h"
#include "../Header/GlobalDef.h"
#include "../Header/UART.h"
#include <util/delay.h>

uint8_t ADC_Read(uint8_t channel)
{
  uint8_t ADC_data;
  volatile char *ADC_address = (char *) 0x1400;
  
  ADC_address[0] = 0x40;
  _delay_us(100);
  ADC_data = ADC_address[0];
   
   return ADC_data;
}
