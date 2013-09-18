﻿/***************************************************************************//**
 *   @file   Oled.c
 *   @brief  Implements the functions to write to the Oled-Display on the USB-
 *            Multifunction Card
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/  

#include "../Header/font_5x7.h"
#include "../Header/Oled.h"
#include <avr/pgmspace.h>


void write_c (unsigned char command)
{
  volatile char *oled_command = (char *) 0x1000; // Address for writting a command to the OLED
  oled_command[0] = command;    
}

void write_d (char data_to_write)
{
  volatile char *oled_data = (char *) 0x1200; // Address for writting a command to the OLED
  oled_data[0] = data_to_write;
}

void Oled_Init(void)
{
  write_c(0xae); // display off
  write_c(0xa1); //segment remap
  write_c(0xda); //common pads hardware: alternative
  write_c(0x12);
  write_c(0xc8); //common output scan direction:com63~com0
  write_c(0xa8); //multiplex ration mode:63
  write_c(0x3f);
  write_c(0xd5); //display divide ratio/osc. freq. mode
  write_c(0x80);
  write_c(0x81); //contrast control
  write_c(0x50);
  write_c(0xd9); //set pre-charge period
  write_c(0x21);
  write_c(0x20); //Set Memory Addressing Mode
  write_c(0x02);
  write_c(0xdb); //VCOM deselect level mode
  write_c(0x30);
  write_c(0xad); //master configuration
  write_c(0x00);
  write_c(0xa4); //out follows RAM content
  write_c(0xa6); //set normal display
  write_c(0xaf); // display on
}

void Oled_put_char (char char_to_print)
{
  unsigned char a;
  
  if(char_to_print < 32)
  {
    char_to_print = 32;
  }
  
  if (char_to_print > 126)
  {
    char_to_print = 126;
  }
  
  char_to_print = char_to_print - 32;
  
  for (a=0; a<5; a++)
  {
    write_d(pgm_read_byte(&myfont[char_to_print][a]));
  }
  write_d(0x00);
}

void Oled_home(void)
{
  //This is for Page addressing mode
  write_c(0X20);
  write_c(0X02);
  
  //This is for setting the columns to be used
  write_c(0x00);
  write_c(0x10);
  //Start page address
  write_c(0xb0);     
}

void Oled_goto_line(unsigned char line)
{  
  //This is for Page addressing mode
  write_c(0X20);
  write_c(0X02);
  
  //This is for setting the columns to be used
  write_c(0x00);
  write_c(0x10);
  //Start page address
  if ((line >= 0) && (line < 8))
  {
    line = line | 0xb0;
    write_c(line);
  }
  else
  {
    write_c(0xb0);
  }      
}

void Oled_clear_line(unsigned char line_to_clear)
{
  Oled_goto_line(line_to_clear);
  unsigned char a;
  for (a=0; a<128; a++)
  {
    write_d(0x00);
  }    
}

void Oled_clear_screen(void)
{    
  Oled_clear_line(0);
  Oled_clear_line(1);
  Oled_clear_line(2);
  Oled_clear_line(3);
  Oled_clear_line(4);
  Oled_clear_line(5);
  Oled_clear_line(6);
  Oled_clear_line(7);
}

void Oled_pos(unsigned char page_num, unsigned char Col_num)
{
  unsigned char temp_Col;
  Oled_goto_line(page_num);
  if (Col_num > 21)
  {
    Col_num = 21;
  }
  //To obtain the column number, the character number has to be multiplied by the number of column each character uses
  Col_num = Col_num * 6;
  //Get the higher four bit of the column address  
  temp_Col = Col_num >> 4;
  temp_Col =  temp_Col & 0x0F;
  //Set the command for the four higher column bits
  temp_Col = temp_Col | 0x10;
  write_c(temp_Col);
  //Set the command for the four lower column bits 
  temp_Col = Col_num & 0x0F;  
  write_c(temp_Col);
}

void Oled_print( char * pChar_to_print)
{
  unsigned char i = 0;
  while ((pChar_to_print[i] != '\0')&&(i < 21))
  {
    Oled_put_char(pChar_to_print[i]);
    i++;
  }    
}

void Oled_Refresh(struct MenuStruct * ptrMenu)
{
  unsigned char Menu_Lenght,i;
  Menu_Lenght = pgm_read_byte(&MenuList[ptrMenu->Menu_to_print][MENU_SIZE_POS]);
  Oled_clear_screen();
  Oled_pos(1,5);
  Oled_print((char *)pgm_read_word(&MenuList[ptrMenu->Menu_to_print][MENU_TITLE_POS]));  
  Oled_pos(3,2);
  for (i = 1; i <= Menu_Lenght; i++)
  {
    if (ptrMenu->SelectedMenu == i)
    {
      Oled_put_char('x');
    }
    else
    {
      Oled_put_char(' ');      
    }
    Oled_print((char *)pgm_read_word(&MenuList[ptrMenu->Menu_to_print][MENU_FIRST_OPTION_POS + i - 1]));
    Oled_pos(i+3,2);
  }
}