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

unsigned char ADC_Read(unsigned char channel)
{
  unsigned char ADC_data;
  volatile unsigned char * ADC_address = (unsigned char *) 0x1400;
  
  ADC_address[0] = channel;
  _delay_us(100);
  ADC_data = ADC_address[0];
   
  return ADC_data;
}
