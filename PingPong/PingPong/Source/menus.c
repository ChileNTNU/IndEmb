/***************************************************************************//**
 *   @file   menus.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#include "../Header/Menus.h"

const char SizeMain[]  PROGMEM = "4";
const char TitleMain[] PROGMEM = "MAIN MENU";
const char MainOne[]   PROGMEM = "Item 1";
const char MainTwo[]   PROGMEM = "Item 2";
const char MainThree[] PROGMEM = "Item 3";
const char MainFour[]  PROGMEM = "Item 4";

const char SizeSubA[]  PROGMEM = "4";
const char TitleSubA[] PROGMEM = "SUB MENU1";
const char SubAOne[]   PROGMEM = "SubItem A1";
const char SubATwo[]   PROGMEM = "SubItem A2";
const char SubAThree[] PROGMEM = "SubItem A3";
const char SubAFour[]  PROGMEM = "BACK";

const char SizeSubB[]  PROGMEM = "4";
const char TitleSubB[] PROGMEM = "SUB MENU2";
const char SubBOne[]   PROGMEM = "SubItem B1";
const char SubBTwo[]   PROGMEM = "SubItem B2";
const char SubBThree[] PROGMEM = "SubItem B3";
const char SubBFour[]  PROGMEM = "BACK";

const char * const MainMenu[] PROGMEM = {
  SizeMain,           //Menu Size
  TitleMain,          //Menu Title
  MainOne,            //First menu option
  MainTwo,
  MainThree,
  MainFour
};

const char * const SubMenu1[] PROGMEM = {
  SizeSubA,
  TitleSubA,
  SubAOne,
  SubATwo,
  SubAThree,
  SubAFour
};

const char * const SubMenu2[] PROGMEM = {
  SizeSubB,
  TitleSubB,
  SubBOne,
  SubBTwo,
  SubBThree,
  SubBFour
};

/*                     
      1         2          1. The data type, a pointer const to char
------------ -------       2. Another const pointer to another pointer
|          | |      |     */
const char * const * const MenuList[] PROGMEM = {
  MainMenu,
  SubMenu1,
  SubMenu2
};



const char MainMenuSelect[] PROGMEM = {
  1, //SubMenu1ID,
  2, //SubMenu2ID,
  0, //MainMenuID,
  0  //MainMenuID  
};

const char Sub1Select[] PROGMEM = {
  0, //MainMenuID,
  0, //MainMenuID,
  0, //MainMenuID,
  0  //MainMenuID
};

const char Sub2Select[] PROGMEM = {
  0, //MainMenuID,
  0, //MainMenuID,
  0, //MainMenuID,
  0  //MainMenuID
};

const char * const AllMenuSelect[] PROGMEM = {
  MainMenuSelect,
  Sub1Select,
  Sub2Select  
};