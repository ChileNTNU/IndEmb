/***************************************************************************//**
 *   @file   menus.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#include "../Header/menus.h"

const char SizeMain[]  PROGMEM = "4";
const char TitleMain[] PROGMEM = "MAIN MENU";
const char MainOne[]   PROGMEM = "Item 1";
const char MainTwo[]   PROGMEM = "Item 2";
const char MainThree[] PROGMEM = "Item 3";
const char MainFour[]  PROGMEM = "Item 4";

const char SizeSubA[]  PROGMEM = "4";
const char TitleSubA[] PROGMEM = "SUB MENU1";
const char SubAOne[]   PROGMEM = "SubItem 1";
const char SubATwo[]   PROGMEM = "SubItem 2";
const char SubAThree[] PROGMEM = "SubItem 3";
const char SubAFour[]  PROGMEM = "BACK";

char * const MainMenu[] PROGMEM = {
  SizeMain,           //Menu Size
  TitleMain,          //Menu Title
  MainOne,            //First menu option
  MainTwo,
  MainThree,
  MainFour
};

char * const SubMenu1[] PROGMEM = {
  SizeSubA,
  TitleSubA,
  SubAOne,
  SubATwo,
  SubAThree,
  SubAFour
};

/*                     
      1         2          1. The data type, a pointer const to char
------------ -------       2. Another const pointer to another pointer
|          | |      |     */
char * const * const MenuList[] PROGMEM = {
  MainMenu,
  SubMenu1
};