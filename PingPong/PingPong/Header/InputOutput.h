/*
 * InputOutput.h
 *
 * Created: 11/09/2013 11:11:47 a. m.
 *  Author: Emilio García
 */ 


#ifndef INPUTOUTPUT_H_
#define INPUTOUTPUT_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern union Ubyte_def ButtonsFlags;    

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define bfJoyButtFlag           ButtonsFlags.Ubit.b0      // Flag for Joystick button
#define bfLeftButtFlag          ButtonsFlags.Ubit.b1      // Flag for Left button
#define bfRightButtFlag         ButtonsFlags.Ubit.b2      // Flag for Right button
#define bfPrevJoyButt           ButtonsFlags.Ubit.b3      // Previous value for the Joystick button
#define bfPrevLeftButt          ButtonsFlags.Ubit.b4      // Previous value for the Left button
#define bfPrevRightButt         ButtonsFlags.Ubit.b5      // Previous value for the Right button

/******************************************************************************/
/* Macros for the registers                                                   */
/******************************************************************************/
#define bfJoyButtonDir   REGISTER_BIT(DDRB,1)
#define bfJoyButton      REGISTER_BIT(PINB,1)
#define bfJoyButtonPull  REGISTER_BIT(PORTB,1)

#define bfLeftButtonDir  REGISTER_BIT(DDRB,2)
#define bfLeftButton     REGISTER_BIT(PINB,2)

#define bfRightButtonDir REGISTER_BIT(DDRB,3)
#define bfRightButton    REGISTER_BIT(PINB,3)

#define bfHeartbeatDir   REGISTER_BIT(DDRE,2)
#define bfHeartbeat      REGISTER_BIT(PORTE,2)


/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void IO_Init(void);
void ReadButtons (void);

#endif /* INPUTOUTPUT_H_ */