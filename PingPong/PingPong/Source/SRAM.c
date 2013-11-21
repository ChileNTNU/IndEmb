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
#include "../Header/Menus.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Initializes the external memory interface.
 * @param   None.
 * @return 	None.
 * @date	  04.09.2013 
*******************************************************************************/
void ExMem_Init(void)
{
  MCUCR |= (1 << SRE);  // Enable external memory
  SFIOR |= (1 << XMM2); // release Pins for JTAG
}

/***************************************************************************//**
 * @brief 	Testfunction for the whole SRAM.
 * @param   None.
 * @return 	None.
 * @date	  04.09.2013 
*******************************************************************************/
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

/***************************************************************************//**
 * @brief 	Stores one byte at the given address in SRAM
 * @param   data    data which is saved in the SRAM
 * @param   address address where the data is saved
 * @return 	None.
 * @date	  04.09.2013 
*******************************************************************************/
void SRAM_Store_Byte(unsigned char data, unsigned int address)
{
  volatile char *ext_ram = (char *) 0x1800;
  ext_ram = ext_ram + address;
  *ext_ram = data;
}

/***************************************************************************//**
 * @brief 	Reads one byte from the SRAM.
 * @param   address address the data is read from
 * @return 	None.
 * @date	  04.09.2013 
*******************************************************************************/
unsigned char SRAM_Read_Byte(unsigned int address)
{
  volatile char *ext_ram = (char *) 0x1800;
  ext_ram = ext_ram + address;
  return *ext_ram;
}

/***************************************************************************//**
 * @brief 	Stores the corresponding font for the OLED in the SRAM
 * @param   char_to_print   char which should be saved in SRAM
 * @param   start_address   address the data is written to
 * @return 	None.
 * @date	  21.09.2013 
*******************************************************************************/
void SRAM_Store_Font(char char_to_print, unsigned int start_address)
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
    SRAM_Store_Byte(pgm_read_byte(&myfont[char_to_print][a]),start_address);
    start_address++;
  }
  SRAM_Store_Byte(0x00,start_address);   
}

/***************************************************************************//**
 * @brief 	Stores a string in a page (127 x 8 byte) in the SRAM
 * @param   String_to_save  string which is saved in the SRAM  
 * @param   Page            page where the data is written to
 * @return 	None.
 * @date	  23.09.2013 
*******************************************************************************/
void SRAM_Store_Page(char * String_to_save, unsigned int Page)
{
  unsigned char i = 0;
    
  while ((String_to_save[i] != '\0')&&(i < 21))
  {
    SRAM_Store_Font(String_to_save[i],Page + (i*6));
    i++;
  }
  SRAM_Store_Byte(0x00,Page + (i*6));         
}

/***************************************************************************//**
 * @brief 	Stores string from program memory in SRAM
 * @param   pChar_to_print    pointer to first character of the string
 * @param   Address           address the data is read from
 * @return 	None.
 * @date	  23.09.2013 
*******************************************************************************/
void SRAM_Store_String_P(const char * pChar_to_print, unsigned int Address)
{
  unsigned char i = 0;
  unsigned char Value_to_print;
  Value_to_print = pgm_read_byte(pChar_to_print);
  
  while ((Value_to_print != '\0')&&(i < 21))
  {    
    SRAM_Store_Font(Value_to_print,Address + (i * 6));
    i++;
    Value_to_print = pgm_read_byte(&pChar_to_print[i]);
  }   
}

/***************************************************************************//**
 * @brief 	Fills the whole SRAM with blanks.
 * @param   None.
 * @return 	None.
 * @date	  23.09.2013 
*******************************************************************************/
void SRAM_Clean (void)
{
  int SRAMaddress =  PAGE0;  
  
  for (SRAMaddress = 0; SRAMaddress < 0x800; SRAMaddress++)
  {
    SRAM_Store_Byte(0x00,SRAMaddress);
  }
}

/***************************************************************************//**
 * @brief 	Saves the current menu figures in the SRAM
 * @param   ptrMenu    pointer to the menu which is used
 * @return 	None.
 * @date	  23.09.2013 
*******************************************************************************/
void SRAM_Refresh_Menu(struct MenuStruct * ptrMenu)
{
  int SRAMaddress;
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
  SRAM_Clean();
  //Oled_pos(1,5);
  SRAMaddress = PAGE1 + 30; //Fifth character, each character has 6 columns
  
  //---Read the pointer of the title string and print it on the Oled---  
  MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_TITLE_POS]);
    
  SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);
  
  //---Go to the start position of the Menu option---
  //Oled_pos(3,2);
  SRAMaddress = PAGE3 + 12; //Second character, each character has 6 columns
  
  for (i = 1; i <= MenuLenght; i++)
  {
    //---Check if the menu which is going to be printed is the selected one---
    if (ptrMenu->SelectedMenu == i)
    {
      SRAM_Store_Font(0xFF,SRAMaddress); //Very last font. In this case the smiley face :)
    }
    else
    {
      SRAM_Store_Font(' ',SRAMaddress);
    }
    //---Print the corresponding menu option---
    MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
    // The +i-1 is because the index of the option menu is not corresponding to the index of this for loop
    ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_FIRST_OPTION_POS + i - 1]);
        
    SRAMaddress = SRAMaddress + 6; //Go to next character
    SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);   
    
    //---Go to the next position of the next menu option
    //Oled_pos(i+3,2);
    SRAMaddress = (PAGE_SIZE * i) + PAGE3 + 12;
  }  
}

/***************************************************************************//**
 * @brief 	Saves the current menu and some items in the SRAM. This is for menu GAME_ON
 * @param   ptrMenu      pointer to the menu which is used
 * @param   Goals_index  index of which goals to display
 * @param   Timer        timer for the game
 * @return 	None.
 * @date	  23.10.2013 
*******************************************************************************/
void SRAM_Refresh_Menu_GAME_ON(struct MenuStruct * ptrMenu, unsigned char * Goals_index, struct TimerStruct * Timer)
{
  int SRAMaddress;
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
  
  //---Clear the SRAM memory and go to the first position, in this case the tittle of the menu---
  SRAM_Clean();  
  SRAMaddress = PAGE1 + 30; //Fifth character, each character has 6 columns
  
  //---Read the pointer of the title string and print it on the SRAM---  
  MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_TITLE_POS]);
    
  SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);
  
  //---Go to the start position of the Menu option---  
  SRAMaddress = PAGE3 + 12; //Second character, each character has 6 columns
  
  for (i = 1; i <= MenuLenght; i++)
  {
    //---Check if the menu which is going to be printed is the selected one---
    if (ptrMenu->SelectedMenu == i)
    {
      SRAM_Store_Font(0xFF,SRAMaddress); //Very last font of the ascii table. In this case the smiley face :)
    }
    else
    {
      SRAM_Store_Font(' ',SRAMaddress);
    }
    //---Print the corresponding menu option---
    MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
    // The +i-1 is because the index of the option menu is not corresponding to the index of this for loop
    ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_FIRST_OPTION_POS + i - 1]);
        
    SRAMaddress = SRAMaddress + 6; //Go to next character
    SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);       
    
    //TODO Print the items
    //SRAM_Store_Font(0xFF,SRAMaddress)
    SRAMaddress = SRAMaddress + 36; //Go to next six characters, in other words jump the word for the option and leave a space
    //Select which option to print depending on how many goals the game has
    switch(i)
    {
      case 1:
        //Print the goals
        ItemFromMenu = (char *) pgm_read_word(&GoalsItems[*Goals_index]);
        SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);      
        break;
      case 2:
        //Print the timer
        //Each digital have to be added 0x30 to convert it into ascii for printing it
        SRAM_Store_Font((Timer->Dmin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((Timer->Umin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font(':',SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((Timer->Dsec)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((Timer->Usec)+0x30,SRAMaddress);
        break;
      case 3:
        break;
      default:
        break;
    }
    
    //---Go to the next position of the next menu option        
    SRAMaddress = (PAGE_SIZE * i) + PAGE3 + 12;
  }  
}

/***************************************************************************//**
 * @brief 	Saves the current menu and some items in the SRAM. This is for menu HIGH_SCORES
 * @param   ptrMenu      pointer to the menu which is used
 * @param   TimerA       timer for highscoreA
 * @param   TimerB       timer for highscoreB
 * @param   TimerC       timer for highscoreC
 * @return 	None.
 * @date	  23.10.2013 
*******************************************************************************/
void SRAM_Refresh_Menu_HIGHSCORES(struct MenuStruct * ptrMenu, struct TimerStruct * TimerA, struct TimerStruct * TimerB, struct TimerStruct * TimerC)
{
  int SRAMaddress;
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
  
  //---Clear the SRAM memory and go to the first position, in this case the tittle of the menu---
  SRAM_Clean();  
  SRAMaddress = PAGE1 + 30; //Fifth character, each character has 6 columns
  
  //---Read the pointer of the title string and print it on the SRAM---  
  MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_TITLE_POS]);
    
  SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);
  
  //---Go to the start position of the Menu option---  
  SRAMaddress = PAGE3 + 12; //Second character, each character has 6 columns
  
  for (i = 1; i <= MenuLenght; i++)
  {
    //---Check if the menu which is going to be printed is the selected one---
    if (ptrMenu->SelectedMenu == i)
    {
      SRAM_Store_Font(0xFF,SRAMaddress); //Very last font of the ascii table. In this case the smiley face :)
    }
    else
    {
      SRAM_Store_Font(' ',SRAMaddress);
    }
    //---Print the corresponding menu option---
    MenuAddress = (int *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
    // The +i-1 is because the index of the option menu is not corresponding to the index of this for loop
    ItemFromMenu = (char *) pgm_read_word(&MenuAddress[MENU_FIRST_OPTION_POS + i - 1]);
        
    SRAMaddress = SRAMaddress + 6; //Go to next character
    SRAM_Store_String_P((const char *)ItemFromMenu,SRAMaddress);       
        
    SRAMaddress = SRAMaddress + 48; //Go to next eight characters, in other words jump the word for the option and leave a space
    //Select which option to print depending on how many goals the game has
    switch(i)
    {
      case 1:
        //Print the timer A
        //Each digital has to be added 0x30 to convert it into ascii for printing it
        SRAM_Store_Font((TimerA->Dmin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerA->Umin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font(':',SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerA->Dsec)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerA->Usec)+0x30,SRAMaddress);
        break;
      case 2:
        //Print the timer B
        //Each digital have to be added 0x30 to convert it into ascii for printing it
        SRAM_Store_Font((TimerB->Dmin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerB->Umin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font(':',SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerB->Dsec)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerB->Usec)+0x30,SRAMaddress);
        break;
      case 3:
        //Print the timer C
        //Each digital have to be added 0x30 to convert it into ascii for printing it
        SRAM_Store_Font((TimerC->Dmin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerC->Umin)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font(':',SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerC->Dsec)+0x30,SRAMaddress);
        SRAMaddress = SRAMaddress + 6;
        SRAM_Store_Font((TimerC->Usec)+0x30,SRAMaddress);
        break;
        break;
      default:
        break;
    }
    
    //---Go to the next position of the next menu option        
    SRAMaddress = (PAGE_SIZE * i) + PAGE3 + 12;
  }  
}