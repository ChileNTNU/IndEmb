﻿/***************************************************************************//**
 *   @file   Controller.h
 *   @brief  Header file to Controller.c
 *	 @date	 6.11.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/CAN.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Definitions for flags                                                      */
/******************************************************************************/

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define K_P                 (12)    
#define K_I                 (1)
#define K_D1                (1)
#define K_D2                (1)
#define T_SAMPLE_MS         (100)
#define POSITION_THRESHOLD  (8)   //This is in percentage

/******************************************************************************/
/* Register definitions                                                       */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Motor_Control(struct ControlStruct * Controller, struct EncoderStruct * Encoder, CANStruct * CAN_Message);

#endif /* CONTROLLER_H_ */