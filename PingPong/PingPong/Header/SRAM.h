/***************************************************************************//**
 *   @file   GlobalDef.h
 *   @brief  Global definitions header file
 *	 @date	 27.08.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef SRAM_H_
#define SRAM_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/


/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define PAGE0    (0x000)
#define PAGE1    (0x100)
#define PAGE2    (0x200)
#define PAGE3    (0x300)
#define PAGE4    (0x400)
#define PAGE5    (0x500)
#define PAGE6    (0x600)
#define PAGE7    (0x700)

#define PAGE_SIZE (0x100)
/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/

void ExMem_Init(void);
void SRAM_test(void);
void SRAMStoreByte(unsigned char data, unsigned int address);
unsigned char SRAMReadByte(unsigned int address);
void SRAMStoreFont(char char_to_print, unsigned int start_address);
void SRAMStorePage(char * String_to_save, unsigned int Page);
void SRAMStoreString_P(const char * pChar_to_print, unsigned int Page);
void SRAMclean (void);
void SRAM_Refresh_Menu(struct MenuStruct * ptrMenu);

#endif /* SRAM_H_ */