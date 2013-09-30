/***************************************************************************//**
 *   @file   UART.c
 *   @brief  Communication file
 *	 @date	 28.08.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/GlobalDef.h"
#include "../Header/UART.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
uint8_t RxData;

/***************************************************************************//**
 * @brief 	Initializes the serial communication over the UART
 * @param   None.
 * @return 	None.
 * @date	  28.08.2013 
*******************************************************************************/
void UART_Init(void)
{ 
  UCSR0A =   (0<<RXC0)|               //Receive complete flag clear
             (0<<TXC0);               //Transmit complete flag clear
  UCSR0B =   (0<<RXCIE0)|             //Rx Interrupt Disable
             (0<<TXCIE0)|             //Tx Interrupt Disable
             (0<<RXEN0)|              //USART Receiver Disable
             (0<<TXEN0);              //USART Transmitter Disable
  UCSR0C =   (1<<URSEL0)|             //For accessing the UCSRC register
             (0<<UMSEL0)|             //Asynchronous mode
             (0<<UPM00)|              //No parity
             (0<<UPM01)|              //No parity
             (0<<USBS0)|              //One Stop Bit
             (1<<UCSZ01)|
             (1<<UCSZ00);             //Character size 8
  UBRR0L =  (uint8_t)UBRR_VALUE & 0xFF;
  UBRR0H =  (uint8_t)(UBRR_VALUE >> 8);     //Sets the Baud Rate High Byte
  bfReg_RxD_Enable    =  C_ENABLE;          //Enables Receive
  bfReg_TxD_Enable    =  C_ENABLE;          //Enables Transmission
  bfReg_RxInterEnable =  C_ENABLE;          //Enables Reception Interrupt
  bfReg_TxInterEnable =  C_DISABLE;         //Enables Transmission Interrupt
}


/***************************************************************************//**
 * @brief 	Sends a character over the UART.
 * @param   data_to_send  data sent over the UART
 * @param   DummyFile     Dummy Pointer so that printf can be used
 * @return 	None.
 * @date	  28.08.2013 
*******************************************************************************/
int UART_put_char(char data_to_send, FILE* DummyFile)
{
    while(!bfReg_TxBufferEmpty)
    {      
    }
    UDR0 = data_to_send;
    return 0;
}
  
/*
ISR(USART0_TX_vect)
{
  bfReg_TxFlag = C_OFF;
  UDR0 = data_to_send;
}
*/

/***************************************************************************//**
 * @brief 	ISR for receiving data over the UART.
 * @param   None.
 * @return 	None.
 * @date	  28.08.2013 
*******************************************************************************/
ISR(USART0_RXC_vect)
{
  bfReg_RxFlag = C_OFF;  
  RxData = UDR0;
  PORTA ^= 0x01;
}