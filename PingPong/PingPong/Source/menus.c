/***************************************************************************//**
 *   @file   menus.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/Menus.h"

//Main menu
const char SizeMain[]  PROGMEM = "3";
const char TitleMain[] PROGMEM = "MAIN MENU";
const char MainOne[]   PROGMEM = "Play";                   //SubA
const char MainTwo[]   PROGMEM = "Configuration";          //SubB
const char MainThree[] PROGMEM = "High score";             //SubC

//Play menu (SubMenu A)
const char SizeSubA[]  PROGMEM = "2";
const char TitleSubA[] PROGMEM = "PING PONG";
const char SubAOne[]   PROGMEM = "Start";                  //SubA.1
const char SubATwo[]   PROGMEM = "BACK";             

//Game on (SubMenu A.1)
const char SizeSubA1[]  PROGMEM = "3";
const char TitleSubA1[] PROGMEM = "PLAYING";
const char SubA1One[]   PROGMEM = "Lifes";
const char SubA1Two[]   PROGMEM = "Time";
const char SubA1Three[] PROGMEM = "BACK";

//Configuration menu (SubMenu B)
const char SizeSubB[]  PROGMEM = "4";
const char TitleSubB[] PROGMEM = "CONFIGURATION";
const char SubBOne[]   PROGMEM = "Modify A";
const char SubBTwo[]   PROGMEM = "Modify B";
const char SubBThree[] PROGMEM = "Modify C";
const char SubBFour[]  PROGMEM = "BACK";

//High scores menu (SubMenu C)
const char SizeSubC[]  PROGMEM = "4";
const char TitleSubC[] PROGMEM = "HIGH SCORES";
const char SubCOne[]   PROGMEM = "Emilio    1000s";
const char SubCTwo[]   PROGMEM = "Tu papi   1000s";
const char SubCThree[] PROGMEM = "Tu culito 1000s";
const char SubCFour[]  PROGMEM = "BACK";

const char * const MainMenu[] PROGMEM = {
  SizeMain,           //Menu Size
  TitleMain,          //Menu Title
  MainOne,            //First menu option
  MainTwo,
  MainThree  
};

const char * const SubMenuA[] PROGMEM = {
  SizeSubA,
  TitleSubA,
  SubAOne,
  SubATwo
};

const char * const SubMenuA1[] PROGMEM = {
  SizeSubA1,
  TitleSubA1,
  SubA1One,
  SubA1Two,
  SubA1Three
};

const char * const SubMenuB[] PROGMEM = {
  SizeSubB,
  TitleSubB,
  SubBOne,
  SubBTwo,
  SubBThree,
  SubBFour
};

const char * const SubMenuC[] PROGMEM = {
  SizeSubC,
  TitleSubC,
  SubCOne,
  SubCTwo,
  SubCThree,
  SubCFour
};


/*                     
      1         2          1. The data type, a pointer const to char
------------ -------       2. Another const pointer to another pointer
|          | |      |     */
const char * const * const MenuList[] PROGMEM = {
  MainMenu,
  SubMenuA,  
  SubMenuB,
  SubMenuC,
  SubMenuA1
};



//This are the array the tells us on which menu we are (Control Array)
const char MainMenuSelect[] PROGMEM = {
  1, //SubMenuAid,
  2, //SubMenuBid,
  3, //SubMenuCid,
  0  //MainMenuID  
};

const char SubASelect[] PROGMEM = {
  4, //SubMenuA1,
  0  //MainMenuID,  
};

const char SubA1Select[] PROGMEM = {
  0, //MainMenuID,
  0, //MainMenuID,
  0, //MainMenuID,
  0  //MainMenuID
};

const char SubBSelect[] PROGMEM = {
  0, //MainMenuID,
  0, //MainMenuID,
  0, //MainMenuID,
  0  //MainMenuID
};

const char SubCSelect[] PROGMEM = {
  0, //MainMenuID,
  0, //MainMenuID,
  0, //MainMenuID,
  0  //MainMenuID
};

//This is the global list of all menus
const char * const AllMenuSelect[] PROGMEM = {
  MainMenuSelect,    //0  This leads to define MAIN_MENU_ID as 0
  SubASelect,        //1
  SubBSelect,        //2
  SubCSelect,        //3
  SubA1Select        //4
};