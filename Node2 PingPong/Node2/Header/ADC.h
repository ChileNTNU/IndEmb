/***************************************************************************//**
 *   @file   ADC.h
 *   @brief  Header file to ADC.c
 *	 @date	 27.08.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern volatile unsigned char ADC_goal;
extern union Ubyte_def ADCFlags;

/******************************************************************************/
/* Definitions for flags                                                      */
/******************************************************************************/
#define ADCallFlags         ADCFlags.Ubyte        // All interruption flags
#define bfPrevGoalFlag      ADCFlags.Ubit.b0      // Previous value of the Goal flag
#define bfGoalFlag          ADCFlags.Ubit.b1      // New Value
/*
#define bfTxInt0            ADCFlags.Ubit.b2      // Tx flag 0
#define bfTxInt1            ADCFlags.Ubit.b3      // Tx flag 1
#define bfTxInt2            ADCFlags.Ubit.b4      // Tx flag 2
#define bfErrorInt          ADCFlags.Ubit.b5      // Error flag
#define bfWakeUpInt         ADCFlags.Ubit.b6      // Wake up flag
#define bfMessageErrorInt   ADCFlags.Ubit.b7      // Message Error Interrupt
*/

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define GOAL_THRESHOLD       (25)

/******************************************************************************/
/* Register definitions                                                                */
/******************************************************************************/
#define bfADCstart   REGISTER_BIT(ADCSRA,6)

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void ADC_Init(void);
void ADC_Start_Conversion(void);
void Detect_Goal(void);

#endif /* ADC_H_ */