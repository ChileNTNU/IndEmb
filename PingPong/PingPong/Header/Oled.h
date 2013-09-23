/***************************************************************************//**
 *   @file   Oled.h
 *   @brief  Header file to Oled.c
 *	 @date	 16.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/  


#ifndef OLED_H_
#define OLED_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/menus.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
//extern union Ubyte_def ButtonsFlags;

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
//#define bfJoyButtFlag           ButtonsFlags.Ubit.b0      // Flag for Joystick button

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
//#define bfJoyButtonDir   REGISTER_BIT(DDRB,1)


/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void write_c (unsigned char command);
void write_d (char data_to_write);
void Oled_Init(void);
void Oled_put_char (char char_to_print);
void Oled_home(void);
void Oled_goto_line(unsigned char line);
void Oled_clear_line(unsigned char line_to_clear);
void Oled_clear_screen(void);
void Oled_pos(unsigned char page_num, unsigned char Col_num);
void Oled_print(char * pChar_to_print);
void Oled_print_P(const char * pChar_to_print);
void Oled_Refresh(struct MenuStruct * ptrMenu);

#endif /* OLED_H_ */