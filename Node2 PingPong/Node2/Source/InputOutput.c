/***************************************************************************//**
 *   @file   InputOutput.c
 *   @brief  Implements functions to read the touch buttons and the joystick
 *            button from the USB Multifunction card
 *	 @date	 12.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include <avr/io.h>
#include "../Header/GlobalDef.h"
#include <util/delay.h>
#include "../Header/InputOutput.h"
#include "../Header/Timer.h"

/***************************************************************************//**
 * @brief   Initializes all in and outputs
 * @param   None.
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void IO_Init(void)
{
  //For the heartbeat
  pinHeartbeatDir = C_OUT;
  pinHeartbeat    = C_LED_OFF;
  
  //For MotorBox
  //Outputs
  pinResetEncoderDir = C_OUT;
  pinEnableMotorDir = C_OUT;
  pinOEencoderDir = C_OUT;
  pinSelectLowEncDir = C_OUT;
  pinDirMotorDir = C_OUT;
  //Inputs
  pinD0EncDir = C_IN;
  pinD0EncPull = C_ON;
  
  pinD1EncDir = C_IN;
  pinD1EncPull = C_ON;
  
  pinD2EncDir = C_IN;
  pinD2EncPull = C_ON;
  
  pinD3EncDir = C_IN;
  pinD3EncPull = C_ON;
  
  pinD4EncDir = C_IN;
  pinD4EncPull = C_ON;
  
  pinD5EncDir = C_IN;
  pinD5EncPull = C_ON;
  
  pinD6EncDir = C_IN;
  pinD6EncPull = C_ON;
  
  pinD7EncDir = C_IN;
  pinD7EncPull = C_ON;
    
  //Set pin for ADC as input
  DDRF  &= ~(1<<PF0);
    
  //Setting pin for PWM
  DDRB  |= (1<<PB5);
  
  //Setting pin for receiving the interrupt from the CAN controller
  //Setting PD2 as input
  DDRD &= ~(1<<PD2);
  //Enable Pullup on interrupt pin
  PORTD |= (1<<PD2);
  //Enable interrupt on falling edge
  EICRA |= (1 << ISC21);
  //Enable INT2
  EIMSK |= (1 << INT2);
}

/***************************************************************************//**
 * @brief   Refreshes the PWM compare value depending on Joystick position
 * @param   Message   This is the CAN message coming from Node 1 which contains the Direction of the Joystick
 * @return 	None.
 * @date	  21.10.2013 
*******************************************************************************/
void Servo_Position(CANStruct * Message)
{
  switch (Message->data[0])
    {
    case Left:
      OCR1A = CMP_MAX_2_1MS;      //Accessing the 16 bit register in just one instruction, instead of High and Low  
	    break;
    case Right:
      OCR1A = CMP_MIN_0_9MS;  
      break;
    case Neutral:
      OCR1A = CMP_1_5MS;
      break;
    default:
      OCR1A = CMP_1_5MS;
      break;
    }  
}

/***************************************************************************//**
 * @brief   Reads the encoder 
 * @param   None
 * @return 	Position    it is a 16bits value, which encodes the position
 * @date	  30.10.2013 
*******************************************************************************/
unsigned int Read_Encoder(void)
{
  unsigned char temp;
  unsigned int position;
  //Release the reset pin
  pinResetEncoder = 1;  
  //Set OE encoder low
  pinOEencoder = 0;
  //Set SEL low to get high byte
  pinSelectLowEnc = 0;
  //Wait about 20us
  _delay_us(30);
  //Read MSB
  temp = READ_PORTA;
  position = (temp<<8);
  //Set SEL high to get low byte
  pinSelectLowEnc = 1;
  //Wait about 20us
  _delay_us(30);
  //Read LSB
  temp = READ_PORTA;
  position = position | temp;
  //TODO: Check this line
  //Toggle RST to reset the encoder    
  //Set OE high to disable output of the encoder
  pinOEencoder = 1;
  return position;
}

/***************************************************************************//**
 * @brief   Moves the motor
 * @param   Message   This is the CAN message coming from Node 1 which contains the Direction of the Joystick
 * @return 	None.
 * @date	  30.10.2013 
*******************************************************************************/
void Move_Motor(CANStruct * Message)
{
  if (Message->length != 0)
  {
    switch (Message->data[0])
    {
      case Left:
        pinDirMotor = MOTOR_LEFT;      
        pinEnableMotor = C_ENABLE;
        break;
      case Right:
        pinDirMotor = MOTOR_RIGHT;
        pinEnableMotor = C_ENABLE;
        break;
      case Neutral:
        pinEnableMotor = C_DISABLE;
        break;
      default:      
        break;
    }    
  }
  else
  {
    pinEnableMotor = C_DISABLE;
  }  
}

/***************************************************************************//**
 * @brief   Does an initialization routine
 * @param   None
 * @return 	None
 * @date	  30.10.2013 
*******************************************************************************/
void Motor_Encoder_Init(unsigned int * max_encoder)
{
  //Move the motor to the left and reset the encoder
  pinDirMotor = MOTOR_LEFT;
  pinEnableMotor = C_ENABLE;
  pinResetEncoder = 0;
  _delay_ms(1000);
  pinResetEncoder = 1;  
  
  //Move the motor to the right and read the encoder to get the max value
  pinDirMotor = MOTOR_RIGHT;  
  _delay_ms(1000);  
  * max_encoder = Read_Encoder();
  
  //Move the motor to the center
  pinDirMotor = MOTOR_LEFT;  
  _delay_ms(250);
  pinEnableMotor = C_DISABLE;
  
}