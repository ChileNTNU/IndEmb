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

uint8_t RxData;

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
  bfReg_RxD_Enable    =  C_ENABLE;          // Enables Receive
  bfReg_TxD_Enable    =  C_ENABLE;          // Enables Receive
  bfReg_RxInterEnable =  C_ENABLE;          // Enables Interrupt
  bfReg_TxInterEnable =  C_DISABLE;          // Enables Interrupt
}

int UART_put_char(char data_to_send, FILE* DummyFile)
//int UART_put_char(char data_to_send)
{
    while(!bfReg_TxBufferEmpty)
    {      
    }
    UDR0 = data_to_send;
    return 0;
}

/*
void UART_put_string(char* s)
{
  while (*s)
  {
    UART_put_char(*s,NULL);
    s++;
  }
}  
*/  
  
/*
ISR(USART0_TX_vect)
{
  bfReg_TxFlag = C_OFF;
  UDR0 = data_to_send;
}
*/

ISR(USART0_RXC_vect)
{
  bfReg_RxFlag = C_OFF;  
  RxData = UDR0;
  PORTA ^= 0x01;
}

