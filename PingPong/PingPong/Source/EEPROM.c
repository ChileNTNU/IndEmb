/***************************************************************************//**
 *   @file   EEPROM.c
 *   @brief  File for EEPROM functionality
 *	 @date	 13.11.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/UserInterface.h"
#include "../Header/EEPROM.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/***************************************************************************//**
 * @brief 	Writes a byte to the EEPROM
 * @param   Address    This is the address 
 * @param   Data       This is the data
 * @return 	None.
 * @date	  13.11.2013 
*******************************************************************************/
void EEPROM_Write(unsigned int Address, unsigned char Data)
{
  //Switch off the interrupts
  cli();
  // Wait for completion of previous write
  while(EECR & (1<<EEWE));
  // Set up address and data registers
  EEAR = Address;
  EEDR = Data;
  // Write logical one to EEMWE
  EECR |= (1<<EEMWE);
  // Start eeprom write by setting EEWE
  EECR |= (1<<EEWE);
  //Switch on interrupts
  EnableInterrupts();
}

/***************************************************************************//**
 * @brief 	Reads a byte from the EEPROM
 * @param   Address    This is the address 
 * @return 	EEDR       This is the data
 * @date	  13.11.2013 
*******************************************************************************/
unsigned char EEPROM_Read(unsigned int Address)
{
  //Switch off the interrupts
  cli();
  //Wait for completion of previous write
  while(EECR & (1<<EEWE));
  //Set up address register
  EEAR = Address;
  //Start eeprom read by writing EERE
  EECR |= (1<<EERE);
  //Switch on interrupts
  EnableInterrupts();
  //Return data from data register
  return EEDR;
}

/***************************************************************************//**
 * @brief 	Copies the data from the Timer in RAM into its EEPROM address
 * @param   Address            This is the address 
 * @param   Timer_HighScore    This is a pointer to the timer in RAM
 * @return 	None.
 * @date	  14.11.2013 
*******************************************************************************/
void EEPROM_Set_HighScore(unsigned char Address, struct TimerStruct * Timer_HighScore)
{
  EEPROM_Write(Address,Timer_HighScore->Dmin);
  EEPROM_Write(Address + 1,Timer_HighScore->Umin);
  EEPROM_Write(Address + 2,Timer_HighScore->Dsec);
  EEPROM_Write(Address + 3,Timer_HighScore->Usec);
}

/***************************************************************************//**
 * @brief 	Reads the values from a timer in EEPROM and copies them into the RAM variable of the Timer selected
 * @param   Address            This is the address 
 * @param   Timer_HighScore    This is a pointer to the timer in RAM
 * @return 	None.
 * @date	  14.11.2013 
*******************************************************************************/
void Read_Timer_from_EEPROM(unsigned char Address, struct TimerStruct * Timer_HighScore)
{
  Timer_HighScore->Dmin = EEPROM_Read(Address);
  Timer_HighScore->Umin = EEPROM_Read(Address + 1);
  Timer_HighScore->Dsec = EEPROM_Read(Address + 2);
  Timer_HighScore->Usec = EEPROM_Read(Address + 3);    
}

/***************************************************************************//**
 * @brief 	Reset the timer in RAM and then copies zeros to the addresses in EEPROM
 * @param   Timer_HighA    This is a RAM variable for the first timer
 * @param   Timer_HighB    This is a RAM variable for the second timer
 * @param   Timer_HighC    This is a RAM variable for the third timer
 * @return 	None
 * @date	  14.11.2013 
*******************************************************************************/
void Reset_HighScores(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC)
{
  //Reset all timer to Zero  
  Reset_Timer(Timer_HighA);
  Reset_Timer(Timer_HighB);
  Reset_Timer(Timer_HighC);
  //Set to Zero all the EEPROM addresses
  EEPROM_Set_HighScore(EEPROM_ADDRESS_1,Timer_HighA);
  EEPROM_Set_HighScore(EEPROM_ADDRESS_2,Timer_HighB);
  EEPROM_Set_HighScore(EEPROM_ADDRESS_3,Timer_HighC);
  //Erase the flag, which means no data is into the EEPROM
  EEPROM_Write(EEPROM_ADDRESS_FLAG,WRITTEN_FLAG_NOT_SET);
}

/***************************************************************************//**
 * @brief 	Reads a byte from the EEPROM
 * @param   Address    This is the address 
 * @return 	EEDR       This is the data
 * @date	  13.11.2013 
*******************************************************************************/
void EEPROM_Init(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC)
{
  unsigned char EEPROM_written_flag;
  
  EEPROM_written_flag = EEPROM_Read(EEPROM_ADDRESS_FLAG);
  
  if (EEPROM_written_flag == WRITTEN_FLAG_SET)
  {
    Read_Timer_from_EEPROM(EEPROM_ADDRESS_1,Timer_HighA);
    Read_Timer_from_EEPROM(EEPROM_ADDRESS_2,Timer_HighB);
    Read_Timer_from_EEPROM(EEPROM_ADDRESS_3,Timer_HighC);
  }
  else
  {
    Reset_HighScores(Timer_HighA,Timer_HighB,Timer_HighC);
  }
}

/***************************************************************************//**
 * @brief 	Write the timer on RAM to the EEPROM
 * @param   None
 * @return 	None
 * @date	  13.11.2013 
*******************************************************************************/
void EEPROM_Write_All_Timers(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC)
{
  EEPROM_Set_HighScore(EEPROM_ADDRESS_1,Timer_HighA);
  EEPROM_Set_HighScore(EEPROM_ADDRESS_2,Timer_HighB);
  EEPROM_Set_HighScore(EEPROM_ADDRESS_3,Timer_HighC);  
  //Set the flag, which means data is into the EEPROM
  EEPROM_Write(EEPROM_ADDRESS_FLAG,WRITTEN_FLAG_SET);
}