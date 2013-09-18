/***************************************************************************//**
 *   @file   menus.h
 *   @brief  contains the strings for the menu items
 *	 @date	 18.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef MENUS_H_
#define MENUS_H_

#include "../Header/GlobalDef.h"
#include <avr/pgmspace.h>

#define MENU_SIZE_POS              (0)
#define MENU_TITLE_POS             (1)
#define MENU_FIRST_OPTION_POS      (2)

extern char* const * const MenuList[];

#endif /* MENUS_H_ */