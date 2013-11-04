/***************************************************************************//**
 *   @file   CAN.h
 *   @brief  Header file for CAN.c
 *	 @date	 01.10.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef CAN_H_
#define CAN_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
typedef struct{
  unsigned int  id;
  unsigned char length;
  unsigned char data[8];
  }CANStruct;
  
#define NODE_1_ID       (0xFF01)
#define NODE_1_LENGTH   (0x04)

/******************************************************************************/
/* Macros for the registers. Made by us                                       */
/******************************************************************************/

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
char Can_Init(void);
char Can_Messsage_Send(CANStruct * Message_to_send, char Buffer_num);
void Can_Messsage_Receive(CANStruct * Message_to_send, char Buffer_num);
void Can_Reception(CANStruct * Message_received);
void Can_Print_Message(CANStruct * Message_received);
void Can_Message(CANStruct * Message_to_send, JoyStruct * JoyData, struct SlideStruct * SlidersData);
void Can_Interrupt_Vect(void);
void Can_Clear_Message(CANStruct * Message_to_clear);

/*
void Can_Error(void);
void Can_Transmit_Complete(void);
void Can_Data_Receive(void);
*/

#endif /* CAN_H_ */