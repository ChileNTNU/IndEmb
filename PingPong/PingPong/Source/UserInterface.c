/***************************************************************************//**
 *   @file   UserInterface.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#include "../Header/menus.h"
#include "../Header/UserInterface.h"
#include "../Header/UART.h"
#include <avr/pgmspace.h>

unsigned char MoveSelection (struct MenuStruct *ptrMenu, struct JoyStruct *ptrJoystick)
{
  unsigned char MenuLenght;
  char * DummyLenght;
  //In order to read all the pointer from flash. The step that have to be done are
  //1. First read the pointer from the MenuList
  DummyLenght = (char *) pgm_read_word(&MenuList[ptrMenu->Menu_to_print]);
  //2. Second read the pointer from the Menu which is active
  DummyLenght = (char *) pgm_read_word(&DummyLenght[MENU_SIZE_POS]);
  //3. Third you have to read the actual value from flash
  MenuLenght = pgm_read_byte(DummyLenght);
  //4. Fourth the value has to converted from ascii to normal number by substracting '0' 
  MenuLenght = MenuLenght - '0';
  
  if ((ptrJoystick->PrevDir == Neutral) && (ptrJoystick->Dir == Down))
  {
    ptrMenu->SelectedMenu++;
    if (ptrMenu->SelectedMenu > MenuLenght)
    {
      ptrMenu->SelectedMenu = 1;    //Go to the first menu option
    }
  } 

  return MenuLenght;
} 

