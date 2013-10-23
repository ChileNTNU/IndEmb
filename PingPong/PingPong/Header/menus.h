/***************************************************************************//**
 *   @file   menus.h
 *   @brief  contains the strings for the menu items
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef MENUS_H_
#define MENUS_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include <avr/pgmspace.h>

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define MENU_SIZE_POS              (0)
#define MENU_TITLE_POS             (1)
#define MENU_FIRST_OPTION_POS      (2)

#define MAIN_MENU_ID               (0)
#define PLAY_MENU_ID               (1)
#define CONFIG_MENU_ID             (2)
#define HIGHSCORE_MENU_ID          (3)
#define GAME_ON_MENU_ID            (4)

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern const char * const * const MenuList[];
extern const char * const AllMenuSelect[];

#endif /* MENUS_H_ */