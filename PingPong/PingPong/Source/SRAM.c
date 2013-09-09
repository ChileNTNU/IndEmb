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

void ExMem_Init(void)
{
  MCUCR |= (1 << SRE);  // Enable external memory
  SFIOR |= (1 << XMM2); // release Pins for JTAG
}

void SRAM_test(void)
{
  volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM  
  
  uint16_t i, werrors, rerrors;
  uint8_t testvalue;
  
  werrors = 0;
  rerrors = 0;  
      
  printf("Starting SRAM test...\r\n");
      
  for (i = 0; i < 0x800; ++i)
  {
    testvalue = ~(i % 256);
    ext_ram[i] = testvalue;    
    if (ext_ram[i] != testvalue)
    {    
      printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);      
      ++werrors;
    }
  }
  
  for (i = 0; i < 0x800; ++i)
  {
    testvalue = ~(i % 256);
    if (ext_ram[i] != testvalue)
    {      
      printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);      
      ++rerrors;
    }
  }
  printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);  
}
