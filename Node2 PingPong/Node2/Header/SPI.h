/***************************************************************************//**
 *   @file   SPI.h
 *   @brief  Header file for SPI.c
 *	 @date	 30.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
#define pinSSmcp2515dir         REGISTER_BIT(DDRB,0)      
#define pinMOSIdir              REGISTER_BIT(DDRB,2)
#define pinMISOdir              REGISTER_BIT(DDRB,3)
#define pinSCKdir               REGISTER_BIT(DDRB,1)

#define pinSSmcp2515            REGISTER_BIT(PORTB,0)      //When low the slave is selected, when high the slave is free
#define pinMOSI                 REGISTER_BIT(PORTB,2)
#define pinMISOpull             REGISTER_BIT(PORTB,3)
#define pinSCK                  REGISTER_BIT(PORTB,1)
  
#define bfReg_SPIinterFlag      REGISTER_BIT(SPSR,7)      // This is the flag which is set when an interrupt occurs
#define bfReg_SPIinterEnable    REGISTER_BIT(SPCR,7)      // Interrupt enable flag for SPI

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern unsigned char SPIRxData;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void SPI_Init(void);
void SPI_put_char(unsigned char data_to_send);

#endif /* SPI_H_ */