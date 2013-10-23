/***************************************************************************//**
 *   @file   MCP2515.h
 *   @brief  Header file for MCP2515.c
 *	 @date	 30.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#ifndef MCP2515_H_
#define MCP2515_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/CAN.h"

/******************************************************************************/
/* Definitions                                                                */
/******************************************************************************/
#define DUMMY             (0xFF)

//Buffers number
#define BUFFER_0                (0x00)
#define BUFFER_1                (0x01)

//Command Modes
#define MCP2515_NORMAL_MODE     (0x00)
#define MCP2515_SLEEP_MODE      (0x20)
#define MCP2515_LOOPBACK_MODE   (0x40)
#define MCP2515_LISTEN_MODE     (0x50)
#define MCP2515_CONFIG_MODE     (0x80)

//Commands
#define RESET               (0b11000000)
#define WRITE               (0b00000010)
#define READ                (0b00000011)
#define BIT_MODIFY          (0b00000101)
#define READ_RX_BUFFER      (0b10010000)
#define READ_BUFFER_0_ID    (READ_RX_BUFFER)
#define READ_BUFFER_0_DATA  (READ_RX_BUFFER | 0b00000010)
#define READ_BUFFER_1_ID    (READ_RX_BUFFER | 0b00000100) 
#define READ_BUFFER_1_DATA  (READ_RX_BUFFER | 0b00000110)  
#define LOAD_TX_BUFFER      (0b01000000)
#define LOAD_BUFFER_0_ID    (LOAD_TX_BUFFER)
#define LOAD_BUFFER_0_DATA  (LOAD_TX_BUFFER | 0b00000001)
#define LOAD_BUFFER_1_ID    (LOAD_TX_BUFFER | 0b00000010)
#define LOAD_BUFFER_1_DATA  (LOAD_TX_BUFFER | 0b00000011)
#define LOAD_BUFFER_2_ID    (LOAD_TX_BUFFER | 0b00000100)
#define LOAD_BUFFER_2_DATA  (LOAD_TX_BUFFER | 0b00000101)
#define RTS                 (0b10000000)
#define RTS_TX_BUFFER_0     (RTS | 0b00000001)
#define RTS_TX_BUFFER_1     (RTS | 0b00000010)
#define RTS_TX_BUFFER_2     (RTS | 0b00000100)
#define RTS_ALL_BUFFERS		  (RTS | 0b00000111)
#define READ_STATUS         (0b10100000)
#define RX_STATUS           (0b10110000)

// Define MCP2515 register addresses
#define MCP_RXF0SIDH	0x00
#define MCP_RXF0SIDL	0x01
#define MCP_RXF0EID8	0x02
#define MCP_RXF0EID0	0x03
#define MCP_RXF1SIDH	0x04
#define MCP_RXF1SIDL	0x05
#define MCP_RXF1EID8	0x06
#define MCP_RXF1EID0	0x07
#define MCP_RXF2SIDH	0x08
#define MCP_RXF2SIDL	0x09
#define MCP_RXF2EID8	0x0A
#define MCP_RXF2EID0	0x0B
#define MCP_CANSTAT		0x0E
#define MCP_CANCTRL		0x0F
#define MCP_RXF3SIDH	0x10
#define MCP_RXF3SIDL	0x11
#define MCP_RXF3EID8	0x12
#define MCP_RXF3EID0	0x13
#define MCP_RXF4SIDH	0x14
#define MCP_RXF4SIDL	0x15
#define MCP_RXF4EID8	0x16
#define MCP_RXF4EID0	0x17
#define MCP_RXF5SIDH	0x18
#define MCP_RXF5SIDL	0x19
#define MCP_RXF5EID8	0x1A
#define MCP_RXF5EID0	0x1B
#define MCP_TEC			  0x1C
#define MCP_REC			  0x1D
#define MCP_RXM0SIDH	0x20
#define MCP_RXM0SIDL	0x21
#define MCP_RXM0EID8	0x22
#define MCP_RXM0EID0	0x23
#define MCP_RXM1SIDH	0x24
#define MCP_RXM1SIDL	0x25
#define MCP_RXM1EID8	0x26
#define MCP_RXM1EID0	0x27
#define MCP_CNF3		  0x28
#define MCP_CNF2		  0x29
#define MCP_CNF1		  0x2A
#define MCP_CANINTE		0x2B
#define MCP_CANINTF		0x2C
#define MCP_EFLG		  0x2D
#define MCP_TXB0CTRL	0x30
#define MCP_TXB1CTRL	0x40
#define MCP_TXB2CTRL	0x50
#define MCP_RXB0CTRL	0x60
#define MCP_RXB0SIDH	0x61
#define MCP_RXB1CTRL	0x70
#define MCP_RXB1SIDH	0x71

//Other commands
#define MCP_TX_INT		0x1C		// Enable all transmit interrupts
#define MCP_TX01_INT	0x0C		// Enable TXB0 and TXB1 interrupts
#define MCP_RX_INT		0x03		// Enable receive interrupts
#define MCP_NO_INT		0x00		// Disable all interrupts

#define MCP_TX01_MASK	0x14
#define MCP_TX_MASK		0x54

// CANCTRL Register Values
#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP	  0xE0
#define MODE_MASK		    0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT	  0x08
#define CLKOUT_ENABLE	  0x04
#define CLKOUT_DISABLE	0x00
#define CLKOUT_PS1		  0x00
#define CLKOUT_PS2		  0x01
#define CLKOUT_PS4		  0x02
#define CLKOUT_PS8		  0x03

// CNF1 Register Values
#define SJW1            0x00
#define SJW2            0x40
#define SJW3            0x80
#define SJW4            0xC0

// CNF2 Register Values
#define BTLMODE			    0x80
#define SAMPLE_1X       0x00
#define SAMPLE_3X       0x40

// CNF3 Register Values
#define SOF_ENABLE		  0x80
#define SOF_DISABLE		  0x00
#define WAKFIL_ENABLE	  0x40
#define WAKFIL_DISABLE	0x00

// CANINTF Register Bits
#define MCP_RX0IF		0x01
#define MCP_RX1IF		0x02
#define MCP_TX0IF		0x04
#define MCP_TX1IF		0x08
#define MCP_TX2IF		0x10
#define MCP_ERRIF		0x20
#define MCP_WAKIF		0x40
#define MCP_MERRF		0x80

// TXBxCTRL Transmission buffer control register Bits
#define MCP_TXP0		0x01
#define MCP_TXP1		0x02
#define MCP_TXREQ		0x08
#define MCP_TXERROR	0x10
#define MCP_MLOA		0x20
#define MCP_ABTF		0x40


/******************************************************************************/
/* Macros for the registers. Made by us                                       */
/******************************************************************************/

/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
extern union Ubyte_def CANFlags;
extern volatile unsigned char CAN_Event;

/******************************************************************************/
/* Definitions for flags                                                      */ 
/******************************************************************************/
#define CANintFlags         CANFlags.Ubyte        // All interruption flags
#define bfRxInt0            CANFlags.Ubit.b0      // Rx flag 0
#define bfRxInt1            CANFlags.Ubit.b1      // Rx flag 1
#define bfTxInt0            CANFlags.Ubit.b2      // Tx flag 0
#define bfTxInt1            CANFlags.Ubit.b3      // Tx flag 1
#define bfTxInt2            CANFlags.Ubit.b4      // Tx flag 2
#define bfErrorInt          CANFlags.Ubit.b5      // Error flag
#define bfWakeUpInt         CANFlags.Ubit.b6      // Wake up flag
#define bfMessageErrorInt   CANFlags.Ubit.b7      // Message Error Interrupt

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void MCP2515_Reset(void);
unsigned char MCP2515_Read(unsigned char Address);
void MCP2515_Write(unsigned char Address, unsigned char Data_to_send);
void MCP2515_Bit_Modify(unsigned char Address, unsigned char Mask, unsigned char Data_to_send);
void MCP2515_Load_Tx_Buffer_Header(unsigned char Buffer_to_send, CANStruct * Message_to_send);
void MCP2515_Load_Tx_Buffer_Data(unsigned char Buffer_to_send, CANStruct * Message_to_send);
void MCP2515_Request_to_Send(unsigned char Buffer_to_send);
void MCP2515_Read_Rx_Buffer_Header(unsigned char Cmd_Read_Rx_Buffer, CANStruct * Message_received);
void MCP2515_Read_Rx_Buffer_Data(unsigned char Cmd_Read_Rx_Buffer, CANStruct * Message_received);
unsigned char MCP2515_Read_Status(void);
char MCP2515_Change_Mode(unsigned char MCP2515_Mode);
char MCP2515_Init(void);

#endif /* MCP2515_H_ */