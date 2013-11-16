/***************************************************************************//**
 *   @file   EEPROM.h
 *   @brief  Header file for the EEPROM rutines
 *	 @date	 13.11.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/

#define EEPROM_ADDRESS_1     (0)
#define EEPROM_ADDRESS_2     (10)
#define EEPROM_ADDRESS_3     (20)
#define EEPROM_ADDRESS_FLAG  (30)

#define WRITTEN_FLAG_SET     (0xAA)
#define WRITTEN_FLAG_NOT_SET (0xFF)
#define NUMBER_EEPROM_ITEMS  (4)

#define ITEMS_PER_SCORE (5)

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void EEPROM_Write(unsigned int Address, unsigned char Data);
unsigned char EEPROM_Read(unsigned int Address);

void EEPROM_Set_HighScore(unsigned char Address, struct TimerStruct * Timer_HighScore);
void Read_Timer_from_EEPROM(unsigned char Address, struct TimerStruct * Timer_HighScore);
void Reset_HighScores(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC);
void EEPROM_Init(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC);
void EEPROM_Write_All_Timers(struct TimerStruct * Timer_HighA, struct TimerStruct * Timer_HighB, struct TimerStruct * Timer_HighC);

#endif /* EEPROM_H_ */