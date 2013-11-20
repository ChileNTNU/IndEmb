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
#include "../Header/TWI.h"

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
  
  //For the solenoid
  pinSolenoidDir = C_OUT;
  pinSolenoid    = C_ON;
  
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
 * @param   Position   This is the Direction of the Joystick, which is in the CAN message coming from Node 1
 * @return 	None.
 * @date	  21.10.2013 
*******************************************************************************/
void Servo_Position(unsigned char Position)
{
  switch (Position)
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
 * @brief   Triggers the solenoid depending on the CAN message received
 * @param   Selenoid   This is solenoid trigger, which is in the CAN message coming from Node 1
 * @return 	None
 * @date	  4.11.2013 
*******************************************************************************/
void Solenoid_Trigger(unsigned char Solenoid)
{
  if (Solenoid == 0x01)
  {
    pinSolenoid = C_OFF;
  }
  else
  {
    pinSolenoid = C_ON;
  }
} 


/***************************************************************************//**
 * @brief   Sets the speed depending on the position of the Left slider
 * @param   Speed     This is the speed value we want to set
 * @return 	None
 * @date	  4.11.2013 
*******************************************************************************/
void Set_Speed(unsigned char Speed)
{
  //Array[0] = Address of the DAC
  //Array[1] = Select channel from the DAC to be the output
  //Array[2] = Output value
  unsigned char TWI_Message_to_DAC [3] = {DAC_MAX520_ADDR_WRITE, 0x00, 0x00};
  //Just send the data received from Node 1 to the DAC
  //The data coming from the sliders is already in a range of 0 to 255, which is the same range needed for the DAC
  TWI_Message_to_DAC[2] = Speed;  
  TWI_Start_Transceiver_With_Data(TWI_Message_to_DAC,0x03);
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
 * @brief   Reads the encoder and converts the value into percentage
 * @param   Encoder     Structure containing the offset and range of the encoder
 * @return 	None
 * @date	  30.11.2013 
*******************************************************************************/
void Read_Encoder_Percentage(struct EncoderStruct * Encoder)
{
  unsigned long encoder_position;
  encoder_position = (unsigned long) Read_Encoder();
  encoder_position = encoder_position - Encoder->Offset;
  encoder_position = encoder_position * 100;
  encoder_position = encoder_position /Encoder->Range;
  Encoder->Actual_position = (unsigned char) encoder_position; 
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
 * @brief   Moves the motor based on the controller output
 * @param   Controller   Structure that contains the controller output
 * @return 	None.
 * @date	  30.10.2013 
*******************************************************************************/
void Move_Motor_With_Control(struct ControlStruct * Controller)
{
  switch (Controller->Motor_Direction)
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


/***************************************************************************//**
 * @brief   Does an initialization routine
 * @param   None
 * @return 	None
 * @date	  30.10.2013 
*******************************************************************************/
void Motor_Encoder_Init(struct EncoderStruct * Encoder)
{  
  int max = 0;
  //Define the speed to half speed  
  unsigned char TWI_Message_to_DAC [3] = {DAC_MAX520_ADDR_WRITE, 0x00, 0x7F};
  TWI_Start_Transceiver_With_Data(TWI_Message_to_DAC,0x03);

  //Move the motor to the left and reset the encoder
  pinDirMotor = MOTOR_RIGHT;
  pinEnableMotor = C_ENABLE;  
  _delay_ms(2000);
  pinResetEncoder = 0;
  pinResetEncoder = 1;    
  
  //Move the motor to the left and read the encoder to get the max value
  pinDirMotor = MOTOR_LEFT;  
  _delay_ms(1000);  
  max = Read_Encoder();
  //Move to the right and read the encoder to get the min value
  pinDirMotor = MOTOR_RIGHT;  
  _delay_ms(1000);
  Encoder->Offset = Read_Encoder();    
  Encoder->Range = max - Encoder->Offset;
  
  //Move the motor to the center
  pinDirMotor = MOTOR_LEFT;  
  _delay_ms(250);
  pinEnableMotor = C_DISABLE;  
}