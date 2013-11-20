/***************************************************************************//**
 *   @file   UserInterface.c
 *   @brief  Implements all the functions related to the user interface 
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/Menus.h"
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
void Move_Selection (struct MenuStruct *ptrMenu, JoyStruct *ptrJoystick)
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
  
  //Move the pointer to another position DOWN  
  if ((ptrJoystick->PrevDir == Neutral) && (ptrJoystick->Dir == Down))
  {
    ptrMenu->SelectedMenu++;
    if (ptrMenu->SelectedMenu > MenuLenght)
    {
      ptrMenu->SelectedMenu = 1;    //Go to the first menu option
    }
  } 
  
  //Move the pointer to another position UP
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
  
  //This switch is for selecting fixed options on some menus
  switch(ptrMenu->Menu_to_print)
  {
    case HIGHSCORE_MENU_ID:
      //In case the Menu is the HIGH SCORE one, the only option possible is the fourth one which is BACK
      ptrMenu->SelectedMenu = 4;
      break;
    case GAME_ON_MENU_ID:
      //In case the Menu is the PLAYING one, the only option possible is the Third one which is BACK
      ptrMenu->SelectedMenu = 3;
      break;
    case GAME_OVER_ID:
      //In case the Menu is the GAME OVER, tha smiley face should not appear. That is why it is on the second option which has no letters
      ptrMenu->SelectedMenu = 2;      
    default:
      break;
  }    
} 

/***************************************************************************//**
 * @brief 	Changes between the menus depending on the selected menu.
 * @param   ptrMenu     pointer to menu which is used
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Change_Menu(struct MenuStruct *ptrMenu)
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

/***************************************************************************//**
 * @brief 	Checks if there has been another goal and increases the goals variables.
 * @param   Message     pointer to the CAN message received
 * @param   goals       goals variable
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Check_Goals(CANStruct * Message, unsigned char * goals)
{  
  //If the CAN message received has something and the first data is a goal detection (1)
  if ((Message->length != 0) && (Message->data[0] == 1))
  {    
    * goals = * goals + 1;    
  }
}  

/***************************************************************************//**
 * @brief 	Increases the timer variables for controlling the game time
 * @param   Timer      Structure that controls the time for the game
 * @return 	None.
 * @date	  16.09.2013 
*******************************************************************************/
void Increase_Timer(struct TimerStruct * Timer)
{
  if (Timer->Enable == C_ON)
  {
    Timer->Usec = Timer->Usec + 1;
    if (Timer->Usec == 10)
    {
      Timer->Usec = 0;
      Timer->Dsec = Timer->Dsec + 1;
      if(Timer->Dsec == 6)
      {
        Timer->Dsec = 0;
        Timer->Umin = Timer->Umin + 1;
        if(Timer->Umin == 10)
        {
          Timer->Umin = 0;
          Timer->Dmin = 0;
        }
        if (Timer->Dmin== 6)
        {
          Timer->Dmin = 0;
        }
      }
    }
  }      
}  

/***************************************************************************//**
 * @brief 	Reset the timer selected
 * @param   Timer      Structure of a timer
 * @return 	None.
 * @date	  28.10.2013 
*******************************************************************************/
void Reset_Timer(struct TimerStruct * Timer)
{  
 Timer->Enable = C_OFF;
 Timer->Usec = 0;
 Timer->Dsec = 0;
 Timer->Umin = 0;
 Timer->Dmin = 0;
}

/***************************************************************************//**
 * @brief 	Compares and returns if TimerLow is Higher than TimerLow
 * @param   TimerHigh      Structure of a timer
 * @param   TimerLow       Structure of a timer
 * @return 	Comparison     Returns the result of the comparison
 * @date	  28.10.2013 
*******************************************************************************/
unsigned char Compare_Timers(struct TimerStruct * TimerHigh, struct TimerStruct * TimerLow)
{  
 unsigned char Comparison = C_FALSE;
 
 if (TimerLow->Dmin > TimerHigh->Dmin)
 {
   Comparison = C_TRUE;
 }
 else if (TimerLow->Umin > TimerHigh->Umin)
 {
   Comparison = C_TRUE;
 }
 else if (TimerLow->Dsec > TimerHigh->Dsec)
 {
   Comparison = C_TRUE;
 }
 else if (TimerLow->Usec > TimerHigh->Usec)
 {
   Comparison = C_TRUE;
 }
 return Comparison;
}