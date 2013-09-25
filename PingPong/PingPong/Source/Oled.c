/***************************************************************************//**
 *   @file   Oled.c
 *   @brief  Implements the functions to write to the Oled-Display on the USB-
 *            Multifunction Card
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/  

#include "../Header/font_5x7.h"
#include "../Header/Oled.h"
#include "../Header/SRAM.h"
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Sends a command to the OLED via the external memory interface
 * @param   command   command for the OLED
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void write_c (unsigned char command)
{
  volatile char *oled_command = (char *) 0x1000; // Address for writing a command to the OLED
  oled_command[0] = command;    
}

/***************************************************************************//**
 * @brief 	Sends data to the OLED via the external memory interface
 * @param   data   data for the OLED
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void write_d (char data_to_write)
{
  volatile char *oled_data = (char *) 0x1200; // Address for writing data to the OLED
  oled_data[0] = data_to_write;
}

/***************************************************************************//**
 * @brief 	Initializes the OLED
 * @param   None.
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
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
  //This is for Page addressing mode
  write_c(0X20);
  write_c(0X02);
  
}

/***************************************************************************//**
 * @brief 	Prints a character on the OLED
 * @param   char_to_print   character which is printed
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Oled_put_char (char char_to_print)
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
    write_d(pgm_read_byte(&myfont[char_to_print][a]));
  }
  write_d(0x00);
}

/***************************************************************************//**
 * @brief 	Goes to the first line and the first column
 * @param   None.
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
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

/***************************************************************************//**
 * @brief 	Goes to a specified line.
 * @param   line  line to go to
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
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

/***************************************************************************//**
 * @brief 	Clears the specified line.
 * @param   line_to_clear  line which is cleared
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Oled_clear_line(unsigned char line_to_clear)
{
  Oled_goto_line(line_to_clear);
  unsigned char a;
  for (a=0; a<128; a++)
  {
    write_d(0x00);
  }    
}

/***************************************************************************//**
 * @brief 	Clears the whole OLED.
 * @param   None.
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
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

/***************************************************************************//**
 * @brief 	Goes to a specified line and column.
 * @param   page_num  line/page to go to
 * @param   Col_num   column to go to
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
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

/***************************************************************************//**
 * @brief 	Prints a string on the OLED
 * @param   char_to_print   pointer to the first character to print
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Oled_print( char * pChar_to_print)
{
  unsigned char i = 0;
  while ((pChar_to_print[i] != '\0')&&(i < 21))
  {
    Oled_put_char(pChar_to_print[i]);
    i++;
  }    
}

/***************************************************************************//**
 * @brief 	Prints a string from program memory on the OLED
 * @param   pChar_to_print  pointer to the first character to print
 * @return 	None.
 * @date	  18.09.2013 
*******************************************************************************/
void Oled_print_P( const char * pChar_to_print)
{
  unsigned char i = 0;
  unsigned char Value_to_print;
  Value_to_print = pgm_read_byte(pChar_to_print);
  
  //while ((pgm_read_byte(&pChar_to_print[i]) != '\0')&&(i < 21))
  while ((Value_to_print != '\0')&&(i < 21))
  {
    //Oled_put_char(pgm_read_byte(&pChar_to_print[i]));
    Oled_put_char(Value_to_print);    
    i++;
    Value_to_print = pgm_read_byte(&pChar_to_print[i]);
  }
}

/***************************************************************************//**
 * @brief 	Updates the OLED with the current menu
 * @param   ptrMenu   pointer to Menu which is displayed
 * @return 	None.
 * @date	  18.09.2013 
*******************************************************************************/
void Oled_Refresh(struct MenuStruct * ptrMenu)
{
  unsigned char MenuLenght,i;
  int * MenuAddress;
  char * ItemFromMenu;
  
  //---Read the length of the menu---
  //In order to read all the pointers from flash. The steps that have to be done are
  //1. First read the pointer from the MenuList table. This table has pointer to all the possible menus
  //   We read 16 bits because all pointer in AVR are 16 bit long
  MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  //2. Second read the pointer from the Menu which is active. From here we obtain the address for the
  //   corresponding field we want to use
  ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_SIZE_POS]);
  //3. Third you have to read the actual value from flash. This gets you the value
  MenuLenght = pgm_read_byte(ItemFromMenu);
  //4. Fourth the value has to converted from ascii to normal number by subtracting '0'
  MenuLenght = MenuLenght - '0';      
   
  //---Clear the Oled screen and go to the first position for printing the Title---
  Oled_clear_screen();
  Oled_pos(1,5);
  
  //---Read the pointer of the title string and print it on the Oled---
  MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_TITLE_POS]);
  Oled_print_P((const char *)ItemFromMenu);      
  
  //---Go to the start position of the Menu option---
  Oled_pos(3,2);
  //---Print as many option the menu has
  for (i = 1; i <= MenuLenght; i++)
  {
    //---Check if the menu which is going to be printed is the selected one---
    if (ptrMenu->SelectedMenu == i)
    {
      Oled_put_char(0xFF);
    }
    else
    {
      Oled_put_char(' ');      
    }
    //---Print the corresponding menu option---
    MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
    // The +i-1 is because the index of the option menu is not corresponding to the index of this for loop
    ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_FIRST_OPTION_POS + i - 1]);
    Oled_print_P((const char *)ItemFromMenu);
     
    //Oled_print((char *)pgm_read_word(&MenuList[ptrMenu->Menu_to_print][MENU_FIRST_OPTION_POS + i - 1]));
    
    //---Go to the next position of the next menu option
    Oled_pos(i+3,2);
  }  
}

/***************************************************************************//**
 * @brief 	Refresh one page of the OLED with data from the SRAM
 * @param   PagetoPrint   Page which should be updated
 * @return 	None.
 * @date	  23.09.2013 
*******************************************************************************/
void RefreshPageSRAM(unsigned int PagetoPrint)
{
  unsigned char a, i = 0;
  
  for (i = 0; i < 0x80; i++)
  {
    a = SRAMReadByte(PagetoPrint + i);
    write_d(a);    
  }  
}

/***************************************************************************//**
 * @brief 	Updates the whole OLED with data from the SRAM
 * @param   None.
 * @return 	None.
 * @date	  25.09.2013 
*******************************************************************************/
void OledRefreshFromSRAM(void)
{
  unsigned int PageNum;  
  
  for (PageNum = 0; PageNum < 8; PageNum++)
  {
    Oled_goto_line(PageNum);    
    RefreshPageSRAM(0x100 * PageNum);    
  }
}