/***************************************************************************//**
 *   @file   main.c
 *   @brief  This is the main file for the PingPong project
 *	 @date	 27.08.2013
 *   @author Tobias Franzen and Emilio Garcia
********************************************************************************
 * - Controller:	AVR ATMEGA162
 * - IDE:			ATMEL Studio 6
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Header/GlobalDef.h"
#include <util/delay.h>
#include "../Header/UART.h"
#include "../Header/SRAM.h"
#include "../Header/ADC.h"
#include "../Header/Timer.h"
#include "../Header/InputOutput.h"
#include "../Header/Oled.h"
#include "../Header/font_5x7.h"
#include "../Header/Menus.h"
#include "../Header/UserInterface.h"
#include "../Header/SPI.h"
#include "../Header/MCP2515.h"
#include "../Header/CAN.h"
#include "../Header/Music.h"
#include "../Header/EEPROM.h"
#include <stdio.h>
#include <avr/pgmspace.h>

/***************************************************************************//**
 * @brief 	Main software routine
 * @return 	Integer
 * @date	28.08.2013 
*******************************************************************************/
int main(void)
{  
  //Debug Variables
  unsigned char a,b ;
  //Counter for making a delay during the game
  unsigned char counter_delay = 0;
  //Number of goals
  unsigned char goals = 0;
  //Comparison result from two timers
  unsigned char compare_result = 0;
  //Timers structures
  struct TimerStruct Timer_game  = {C_OFF,0,0,0,0};  //Timer for counting the  duration of the game
  struct TimerStruct Timer_HighA = {C_OFF,0,0,0,0};  //Timer with the first HighScore
  struct TimerStruct Timer_HighB = {C_OFF,0,0,0,0};  //Timer with the second HighScore
  struct TimerStruct Timer_HighC = {C_OFF,0,0,0,0};  //Timer with the third HighScore
  //Data from the Joystick
  JoyStruct Joystick_main;
  //Data from the Sliders
  struct SlideStruct Sliders;
  //Data for controlling the displayed menu and the program flow
  struct MenuStruct Menu;
  Menu.Menu_to_print = 0;
  Menu.SelectedMenu = 1;  
  //CAN message to be send
  CANStruct CAN_message_send = 
  { 0x01A0,
    4,
    {'A','B','C','D','0', '0', '0', '0'}
  };  
  //CAN_message_send.data[0] = 'A';
  //CAN message received
  CANStruct CAN_message_receive = 
  { .id = 0x0000,
    .length = 0
  };
  
  //Initialization routines
  UART_Init();
  ExMem_Init();  
  Timer_Init();
  IO_Init();
  Oled_Init();
  Oled_home();
  SPI_Init();  
  fdevopen(UART_put_char, NULL);  
  EEPROM_Init(&Timer_HighA, &Timer_HighB, &Timer_HighC);
  //EEPROM_Write(EEPROM_ADDRESS_1,0xAA);
    
  EnableInterrupts();
  
  printf("--- Hola ---\r\n");
  SRAM_test();
  SRAM_Clean();
  if (Can_Init() == C_ERROR)
  {
    printf("¡MCP2515 not in configuration mode!");
  }  
  Calibrate_Joystick(&Joystick_main);
  
  //Main program loop  
  while(1)
  {    
    if (bf10msFlag == C_ON)
    {
      bf10msFlag = C_OFF;      
      Read_Buttons();           
    }
    
    if(bf100msFlag == C_ON)
    {
      bf100msFlag = C_OFF;      
      Read_Joystick(&Joystick_main);
      Read_Sliders(&Sliders);
      Move_Selection(&Menu, &Joystick_main);
      //Oled_Refresh(&Menu);                   //Refreshing the OLED from the RAM memory of the microcontroller
        
      //Define actions depending on which menu the user is
      switch (Menu.Menu_to_print)
      {
        case MAIN_MENU_ID:
          SRAM_Refresh_Menu(&Menu);
          Play_Song(TETRIS_SONG);
          //Stop_Music();
          //Play_Tetris();
          break;
        case PLAY_MENU_ID:
          SRAM_Refresh_Menu(&Menu);
          Stop_Music();
          //Reset for the game timer and the goals
          Reset_Timer(&Timer_game);          
          goals = 0;
          counter_delay = 0;
          break;
        case CONFIG_MENU_ID:
          Play_Song(ENTE_SONG);
          SRAM_Refresh_Menu(&Menu);
          break;
        case HIGHSCORE_MENU_ID:
          Play_Song(CUCARACHA_SONG);
          //Different SRAM_Refresh_Menu(&Menu);
          SRAM_Refresh_Menu_HIGHSCORES(&Menu, &Timer_HighA, &Timer_HighB, &Timer_HighC);
          break;
        case GAME_ON_MENU_ID:
          Play_Song(MARIO_SONG);
          Start_Timer(&Timer_game);
          if (goals == 3)
          {
            counter_delay++;
            Stop_Timer(&Timer_game);
            //Check if the score is one of the highest and save it into the EEPROM
            //Check this just one time after the game is over
            if (counter_delay == 1)
            {
              //Routine to compare the high scores and write them to EEPROM
              bfWriteEEPROM = C_FALSE;
              compare_result = Compare_Timers(&Timer_HighA, &Timer_game);
              if (compare_result == C_TRUE)
              {
                Timer_HighC = Timer_HighB;
                Timer_HighB = Timer_HighA;
                Timer_HighA = Timer_game;
                bfWriteEEPROM = C_TRUE;
              }
              else if (Compare_Timers(&Timer_HighB, &Timer_game) == C_TRUE)
              {
                Timer_HighC = Timer_HighB;                
                Timer_HighB = Timer_game;
                bfWriteEEPROM = C_TRUE;
              }
              else if (Compare_Timers(&Timer_HighC, &Timer_game) == C_TRUE)
              {
                Timer_HighC = Timer_game;
                bfWriteEEPROM = C_TRUE;
              }
              
              if (bfWriteEEPROM == C_TRUE)
              {
                EEPROM_Write_All_Timers(&Timer_HighA, &Timer_HighB, &Timer_HighC);
              }
               bfWriteEEPROM = C_FALSE;
            }
            //Wait for 20 times 100ms cycle before going to the Game over screen
            if (counter_delay == 30)
            {
              Menu.Menu_to_print = GAME_OVER_ID;              
              counter_delay = 0;
            }
          }
          else
          {
            //On this menu you need to move Servo depending on the joystick
            //Builds the CAN message with the joystick data
            Can_Message(&CAN_message_send, &Joystick_main, &Sliders);
            Can_Messsage_Send(&CAN_message_send,BUFFER_0);
            //On this menu you need to read if it has scored a goal
            //Checks which interrupt occurred on the CAN controller
            Can_Interrupt_Vect();
            //Receives a message if an interrupt has occurred
            Can_Reception(&CAN_message_receive);
            //Read goals from the CAN message received, and resets the CAN message received
            Check_Goals(&CAN_message_receive, &goals);    
            Can_Clear_Message(&CAN_message_receive);          
          }
          //Different SRAM_Refresh_Menu(&Menu);
          SRAM_Refresh_Menu_GAME_ON(&Menu, &goals, &Timer_game);
          break;
        case GAME_OVER_ID:
          Stop_Music();
          SRAM_Refresh_Menu(&Menu);
          counter_delay++;
          if (counter_delay == 30)
          {
              Menu.Menu_to_print = PLAY_MENU_ID;//Go to the PLAY menu
              Menu.SelectedMenu = 1;//Go to the first option of the PLAY menu         
              counter_delay = 0;
          }
        default:
          break;
      }
        //This is just for normal menus
        //SRAM_Refresh_Menu(&Menu);     
        //Refresh Oled with the data stored on SRAM   
        Oled_Refresh_From_SRAM();                         
    }
    
    if(bf1sFlag == C_ON)
    {
      bf1sFlag = C_OFF;      
      pinHeartbeat = ~pinHeartbeat;
      Increase_Timer(&Timer_game);     
      /*
      if (bfJoyButtFlag == C_ON)
      {
        bfJoyButtFlag = C_OFF;
        //Print_Joystick_Position(&Joystick_main);      //Commented because it has printf        
      }
      */
      
      if (bfLeftButtFlag == C_ON)
      {
        bfLeftButtFlag = C_OFF;
        //Print_Sliders_Position(&Sliders);            //Commented because it has printf
        //Oled display clean        
        //Oled_Clear_Screen();
        //Can_Print_Message(&CAN_message_receive);     //Commented because it has printf
        Change_Menu(&Menu);
      }
      
      /*
      if (bfRightButtFlag == C_ON)
      {
        bfRightButtFlag = C_OFF;        
        //Print_Sliders_Position(&Sliders);                                       
        Can_Messsage_Send(&CAN_message_send,BUFFER_0);                                        
      } 
      */                       
    }    
  }
        
  return 0;
  
  /*
  while(1)
  {        	  
    if (RxData == 0x41)
    {
      PORTA = ~PORTA;
      RxData = 0x00;
    }        
  }
  */  
}