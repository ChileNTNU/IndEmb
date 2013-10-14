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

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Write_Command(unsigned char command);
void Write_Data(char data_to_write);
void Oled_Init(void);
void Oled_put_char(char char_to_print);
void Oled_home(void);
void Oled_goto_line(unsigned char line);
void Oled_clear_line(unsigned char line_to_clear);
void Oled_Clear_Screen(void);
void Oled_pos(unsigned char page_num, unsigned char Col_num);
void Oled_print(char * pChar_to_print);
void Oled_print_P(const char * pChar_to_print);
void Oled_Refresh(struct MenuStruct * ptrMenu);
void Refresh_Page_From_SRAM(unsigned int PagetoPrint);
void Oled_Refresh_From_SRAM(void);

#endif /* OLED_H_ */