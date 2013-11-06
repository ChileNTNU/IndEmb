/***************************************************************************//**
 *   @file   Controller.c
 *   @brief  Closed loop control for the slider position
 *	 @date	 06.11.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/GlobalDef.h"
#include "../Header/Controller.h"
#include "../Header/InputOutput.h"

/***************************************************************************//**
 * @brief 	Calculates the control output for moving the motor
 * @param   Controller   Structure that contains all the controller's variables
 * @param   Encoder      Structure that contains the encoder actual position
 * @param   CAN_Message  Structure that contains desired position
 * @return 	None
 * @date	  06.11.2013 
*******************************************************************************/
void Motor_Control(struct ControlStruct * Controller, struct EncoderStruct * Encoder, CANStruct * CAN_Message)
{
  unsigned char inverted_desired_position, abs_error;
  signed int proportional, integral, diff, temp_diff, total;
  static signed int last_proporcional;
  inverted_desired_position = 100 - CAN_Message->data[3];
  Controller->Error = inverted_desired_position - Encoder->Actual_position;    
    
  //Determine if the motor is with in the threshold position
  if (Controller->Error < 0)
  {
    abs_error = Controller->Error *(-1);
  }
  else
  {
    abs_error = Controller->Error;
  }
  
  if (abs_error <= POSITION_THRESHOLD)
  {
    Controller->Error = 0;
  }  
  
  //Set the motor direction
  if (Controller->Error < 0)
  {
    Controller->Motor_Direction = Right;
  }
  else if (Controller->Error > 0)
  {
    Controller->Motor_Direction = Left;
  }
  else
  {
    Controller->Motor_Direction = Neutral;
  }
  
  //Calculate the control signals
  proportional = K_P * Controller->Error;
  proportional = proportional>>2;                                        //Divide the value by 4
  integral = (signed int)(Controller->Error + Controller->LastError);
  integral = integral>>3;                                                //Divide the value by 8
  integral = Controller->LastIntegral + integral; 
  diff = K_D2*(signed int)(Controller->Error + Controller->LastError);
  diff = diff>>2;                                                        //Divide the value by 4
  temp_diff = (K_D1*Controller->LastDiff)>>1;                            //Divide the value by 2
  diff = diff + temp_diff;
  //diff = K_D1*Controller->LastDiff + K_D2*(signed int)(Controller->Error + Controller->LastError);  
  //integral = Controller->LastIntegral + ((K_I * T_SAMPLE_MS)/2)*(signed int)(Controller->Error + Controller->LastError);
  total = proportional + integral + diff;
    
  //Convert the output to positive for passing it to the speed
  if (total < 0)
  {
    total =  total * (-1);
  }
  
  //Make sure the total is in the range of the speed (0-255)
  if (total > 0xFF)
  {
    total = 0xFF;
  }
  
  
  Controller->Speed = (unsigned char)total;
    
  if (integral > 255)
  {
    integral = 255;
  }
  else if (integral < -255)
  {
    integral = -255;
  }
  
  last_proporcional = proportional;
  Controller->LastIntegral = integral;
  Controller->LastDiff = diff;
  Controller->LastError = Controller->Error;
} 