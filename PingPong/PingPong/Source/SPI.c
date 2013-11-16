/***************************************************************************//**
 *   @file   SPI.c
 *   @brief  SPI communication file
 *	 @date	 30.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/GlobalDef.h"
#include "../Header/SPI.h"
#include "../Header/Timer.h"
#include <util/delay.h>

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
unsigned char SPIRxData = 0;

/***************************************************************************//**
 * @brief 	Initializes the SPI communication
 * @param   None.
 * @return 	None.
 * @date	  30.09.2013 
*******************************************************************************/
void SPI_Init(void)
{ 
  unsigned char dummy_for_reading;
  //Setting the corresponding pins for SPI functionality
  pinSSmcp2515dir  = C_OUT;
  pinMISOdir       = C_IN;
  pinMOSIdir       = C_OUT;
  pinSCKdir        = C_OUT;
  
  pinSSmcp2515     = C_ON;   //Output high
  pinMISOpull      = C_ON;   //Pullup on
  pinMOSI          = C_ON;   //Output high
  pinSCK           = C_ON;   //Output high
  
  SPCR = (1<<SPIE)|     //Enabling SPI interrupt
         (1<<SPE)|      //Enabling SPI module
         (0<<DORD)|     //First send MSB 
         (1<<MSTR)|     //Setting master mode
         (0<<CPOL)|     //Setting Clock polarity: Leading edge is the rising one
         (0<<CPHA)|     //Setting Clock phase:    Leading edge -> sample
         (0<<SPR1)|     //These two bit are for a clock rate of fosc/4
         (0<<SPR0);           
   
   //Clear the interrupt flag by reading SPSR and SPDR
   dummy_for_reading = SPSR;
   dummy_for_reading = SPDR;
}

/***************************************************************************//**
 * @brief 	Sends a character over the SPI.
 * @param   data_to_send  data sent over the SPI
 * @return 	None.
 * @date	  30.09.2013 
*******************************************************************************/
void SPI_put_char(unsigned char data_to_send)
{    
  SPDR = data_to_send;
  _delay_us(10);
  //while (bfReg_SPIinterFlag == C_OFF); //Wait until the transmission is complete 
}
  
/***************************************************************************//**
 * @brief 	ISR for SPI communication. SPI sends and receives at the same time
 * @param   None.
 * @return 	None.
 * @date	  30.09.2013 
*******************************************************************************/
ISR(SPI_STC_vect)
{
  SPIRxData = SPDR; 
}