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
#include "../Header/GlobalDef.h"
#include "../Header/SRAM.h"
#include "../Header/UART.h"
#include <stdio.h>
#include <util/delay.h>

void SRAM_Init(void)
{
  MCUCR |= (1 << SRE);  // Enable external memory
  //MCUCR |= (1 << SRE)|(1 << SRW11)|(1 << SRW10);  // Enable external memory
  //MCUCR = 0b11000000;
  //EMCUCR = 0b00001110;
  SFIOR |= (1 << XMM2); // release Pins for JTAG
}

void SRAM_test(void)
{
  volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
  
  char Buffer_string [100];
  
  uint16_t i, werrors, rerrors;
  
  werrors = 0;
  rerrors = 0;
  
  uint8_t testvalue;
    
  UART_put_string("Starting SRAM test...\r\n");
    
  //ext_ram=(char *)0x1801;
  //UART_put_string("Starting SRAM test. bit 1...\r\n");
  
  //ext_ram=(char *)0x1800;
  //UART_put_string("Starting SRAM test. BIT 0...\r\n");
    
  for (i = 0; i < 0x800; ++i)
  {
    //testvalue = ~(i % 256);
    testvalue = 0xD1;
    ext_ram[i] = testvalue;    
    if (ext_ram[i] != testvalue)
    {
      sprintf(Buffer_string,"SRAM error (write phase): ext_ram[%02X] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
      //UART_put_string("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
      UART_put_string(Buffer_string);
      ++werrors;
    }
  }
  
  for (i = 0; i < 0x800; ++i)
  {
    //testvalue = ~(i % 256);
    testvalue = 0xD1;
    if (ext_ram[i] != testvalue)
    {
      sprintf(Buffer_string,"SRAM error (read phase): ext_ram[%02X] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
      //UART_put_string("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
      UART_put_string(Buffer_string);
      ++rerrors;
    }
  }
  sprintf(Buffer_string,"SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
  //UART_put_string("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors)
  UART_put_string(Buffer_string);
}

void LATCH_test(void)
{
  volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
  //ext_ram[0xFF]=0x00;
  
  ext_ram = (char *) 0x18FF;
  (*ext_ram) = 0x00;
  
  
/*  
  DDRA = (1 << PA0);
  DDRE = (1 << PE1);
  
  PORTA = (1<<PA0);
  
  _delay_ms(10);
  PORTE = (1<<PE1);
  
  _delay_ms(10);
  PORTE = (0<<PE1);
  PORTA = (0<<PA0);
  */
}

