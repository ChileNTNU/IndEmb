/***************************************************************************//**
 *   @file   UART.h
 *   @brief  Header file for UART.c
 *	 @date	 28.08.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef UART_H_
#define UART_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include <stdio.h>

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define BAUD_RATE    (9600UL)                                    //Desired baudrate
#define UBRR_VALUE   ((F_CPU+BAUD_RATE*8)/(BAUD_RATE*16)-1)    
#define BAUD_REAL    (F_CPU/(16*(UBRR_VALUE+1)))
#define BAUD_ERROR   (BAUD_RATE*1000/BAUD_RATE)                  //Error per 1000

#if ((BAUD_ERROR < 990) || (BAUD_ERROR > 1010))
  #error Error desired baud rate bigger than 1 percent
#endif
/* adapted from http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/Der_UART#UART_initialisieren */
/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
#define bfReg_RxFlag            REGISTER_BIT(UCSR0A,7)      // Receive Complete Flag
#define bfReg_TxFlag            REGISTER_BIT(UCSR0A,6)      // Transmit Complete Flag
#define bfReg_TxBufferEmpty     REGISTER_BIT(UCSR0A,5)      // Tx Buffer empty flag

#define bfReg_Rx_InterEnable    REGISTER_BIT(UCSR0B,7)      // Receive Enabled
#define bfReg_Tx_InterEnable    REGISTER_BIT(UCSR0B,6)      // Transmit Interrupt Enabled

#define bfReg_Rx_Enable         REGISTER_BIT(UCSR0B,4)      // Receive  Enable bit
#define bfReg_Tx_Enable         REGISTER_BIT(UCSR0B,3)      // Transmit Enable bit

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern uint8_t RxData;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void UART_Init(void);
int UART_put_char(char data_to_send, FILE* DummyFile);

#endif /* UART_H_ */