/***************************************************************************//**
 *   @file   UserInterface.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/menus.h"
#include "../Header/UserInterface.h"
#include "../Header/UART.h"
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Recognizes the Joystick movement and changes the selected menu.
 * @param   ptrMenu     pointer to menu which is used
 * @param   ptrJoystick pointer to Joystick which is used
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Move_Selection (struct MenuStruct *ptrMenu, struct JoyStruct *ptrJoystick)
{
  unsigned char MenuLenght;
  int * MenuAddress;
  char * ItemFromMenu;
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
    
  if ((ptrJoystick->PrevDir == Neutral) && (ptrJoystick->Dir == Down))
  {
    ptrMenu->SelectedMenu++;
    if (ptrMenu->SelectedMenu > MenuLenght)
    {
      ptrMenu->SelectedMenu = 1;    //Go to the first menu option
    }
  } 
  if ((ptrJoystick->PrevDir == Neutral) && (ptrJoystick->Dir == Up))
  {    
    if (ptrMenu->SelectedMenu == 1)
    {
      ptrMenu->SelectedMenu = MenuLenght;    //Go to the first menu option
    }
    else
    {
      ptrMenu->SelectedMenu--;
    }
  }
} 

/***************************************************************************//**
 * @brief 	Changes between the menus depending on the selected menu.
 * @param   ptrMenu     pointer to menu which is used
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Change_Menu (struct MenuStruct *ptrMenu)
{  
  char * MenuAddress;
  char SelectedMenu;
  //In order to read all the pointers from flash. The steps that have to be done are
  //1. First read the pointer from the MenuList table. This table has pointer to all the possible menus
  //   We read 16 bits because all pointer in AVR are 16 bit long
  MenuAddress = (char *) pgm_read_word(&AllMenuSelect[ptrMenu->Menu_to_print]);
  //2. Second read the pointer from the Menu which is active. From here we obtain the address for the
  //   corresponding field we want to use
  SelectedMenu = pgm_read_byte(&MenuAddress[ptrMenu->SelectedMenu-1]);
  //3. Third you have to read the actual value from flash. This gets you the value
  ptrMenu->Menu_to_print = SelectedMenu;
  ptrMenu->SelectedMenu = 1;  
}