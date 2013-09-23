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
#include "../Header/font_5x7.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

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

void SRAMStoreByte(unsigned char data, unsigned int address)
{
  volatile char *ext_ram = (char *) 0x1800;
  ext_ram = ext_ram + address;
  *ext_ram = data;
}

unsigned char SRAMReadByte(unsigned int address)
{
  volatile char *ext_ram = (char *) 0x1800;
  ext_ram = ext_ram + address;
  return *ext_ram;
}

void SRAMStoreFont(char char_to_print, unsigned int start_address)
{
   unsigned char a;
   
   if(char_to_print < 32)
   {
     char_to_print = 32;
   }
   
   if (char_to_print > 127)
   {
     char_to_print = 127;
   }
   
   char_to_print = char_to_print - 32;
   
   for (a=0; a<5; a++)
   {
     SRAMStoreByte(pgm_read_byte(&myfont[char_to_print][a]),start_address);
     start_address++;
   }
   SRAMStoreByte(0x00,start_address);   
}

void SRAMStorePage(char * String_to_save, unsigned int Page)
{
  unsigned char i = 0;
    
  while ((String_to_save[i] != '\0')&&(i < 21))
  {
    SRAMStoreFont(String_to_save[i],Page + (i*6));
    i++;
  }      
}

void SRAMclean (void)
{
  SRAMStorePage("                      ",PAGE0);
  SRAMStorePage("                      ",PAGE1);
  SRAMStorePage("                      ",PAGE2);
  SRAMStorePage("                      ",PAGE3);
  SRAMStorePage("                      ",PAGE4);
  SRAMStorePage("                      ",PAGE5);
  SRAMStorePage("                      ",PAGE6);
  SRAMStorePage("                      ",PAGE7);
}