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
extern unsigned char ADC_array[4];

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define ADC_CH1 (0X04)
#define ADC_CH2 (0X05)
#define ADC_CH3 (0X06)
#define ADC_CH4 (0X07)

#define JOY_Y_AXIS   (0X04)
#define JOY_X_AXIS   (0X05)
#define SLIDER_RIGHT (0X06)
#define SLIDER_LEFT  (0X07)

#define THRS (20)                  //This threshold value is in percentage, not in ADC units
#define THRS_NEG (-20)              //This threshold value is in percentage, not in ADC units


/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/

unsigned char ADC_Read(unsigned char channel);
void CalibrateJoystick(struct JoyStruct *pointer_Joystick);
void ReadJoystick(struct JoyStruct *pointer_Joystick);
void PrintJoystickPosition(struct JoyStruct * pointer_Joystick);
void ReadSliders(struct SlideStruct * pointer_Sliders);
void PrintSlidersPosition(struct SlideStruct * pointer_Sliders);

#endif /* ADC_H_ */