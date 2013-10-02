/***************************************************************************//**
 *   @file   GlobalDef.h
 *   @brief  Global definitions header file
 *	 @date	 27.08.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define F_CPU                   (4915200)

#define C_OFF                    (0)
#define C_ON                     (1)

#define C_SS_ENABLE              (0)
#define C_SS_DISABLE             (1)

#define C_IN                     (0)
#define C_OUT                    (1)

#define C_TRUE                   (1)
#define C_FALSE                  (0)

#define C_DISABLE                (0)
#define C_ENABLE                 (1)

#define C_LED_ON                 (0)
#define C_LED_OFF                (1)

#define C_ERROR                  (-1)
#define C_SUCCESS                (0)

#define NOP()                    asm("nop")
#define EnableInterrupts()       __asm__ __volatile__ ("sei" ::: "memory")

enum Direction {Right,Left,Up,Down,Neutral};

/******************************************************************************/
/* Unions declarations                                                        */
/******************************************************************************/
struct  Sbit_def
{
	uint8_t  b0:1;
	uint8_t  b1:1;
	uint8_t  b2:1;
	uint8_t  b3:1;
	uint8_t  b4:1;
	uint8_t  b5:1;
	uint8_t  b6:1;
	uint8_t  b7:1;
};

union   Ubyte_def
{
	struct  Sbit_def Ubit;
	uint8_t      Ubyte;
};

struct JoyStruct
{
  signed char Xpos;  
  signed char Ypos;
  signed char Xoffset;
  signed char Yoffset;
  enum Direction PrevDir;
  enum Direction Dir;
};

struct SlideStruct
{
  unsigned char LeftSlider;
  unsigned char RightSlider;
};

struct MenuStruct
{
  unsigned char SelectedMenu;
  unsigned char Menu_to_print;
};

typedef struct
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) (((volatile _io_reg*)&rg)->bit##bt)

#endif /* GLOBALDEF_H_ */
