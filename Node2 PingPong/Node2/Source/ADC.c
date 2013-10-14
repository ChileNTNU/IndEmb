/***************************************************************************//**
 *   @file   ADC.c
 *   @brief  Implements functions to get the position of the slider and the
 *            joystick of the USB-Multifunction Card
 *	 @date	 04.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "../Header/ADC.h"
#include "../Header/GlobalDef.h"
#include "../Header/UART.h"
#include <util/delay.h>

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
unsigned char ADC_array[4];

/***************************************************************************//**
 * @brief 	Reads the ADC value at specific channel using the external memory bus
 * @param   channel   channel from which to read
 * @return 	ADC_data  data which was read from the ADC
 * @date	  09.09.2013 
*******************************************************************************/
unsigned char ADC_Read(unsigned char channel)
{
  unsigned char ADC_data;
  volatile unsigned char * ADC_address = (unsigned char *) 0x1400;
  
  ADC_address[0] = channel;
  _delay_us(100);
  ADC_data = ADC_address[0];
   
  return ADC_data;
} 

/***************************************************************************//**
 * @brief 	Calibrates the joystick by subtracting the offset value
 * @param   pointer_Joystick   pointer to Joystick which is used
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
void Calibrate_Joystick(struct JoyStruct * pointer_Joystick)
{
  unsigned int Joy_X;
  unsigned int Joy_Y;
  Joy_X = (unsigned int)ADC_Read(JOY_X_AXIS);
  Joy_Y = (unsigned int)ADC_Read(JOY_Y_AXIS);  
  pointer_Joystick->Xoffset = Joy_X - 128;
  pointer_Joystick->Yoffset = Joy_Y - 128;    
}

/***************************************************************************//**
 * @brief 	Reads the position of the Joystick and saves the values in the struct
 * @param   pointer_Joystick   pointer to Joystick which is used
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
void Read_Joystick(struct JoyStruct * pointer_Joystick)
{
  unsigned int Joy_X;
  unsigned int Joy_Y;
  signed int Res_X;
  signed int Res_Y;
  Joy_X = (unsigned int)ADC_Read(JOY_X_AXIS);
  Joy_Y = (unsigned int)ADC_Read(JOY_Y_AXIS);
  
  if(pointer_Joystick->Xoffset < Joy_X)
  {
    Joy_X = Joy_X - pointer_Joystick->Xoffset;
  }
  
  if(pointer_Joystick->Yoffset < Joy_Y)
  {
    Joy_Y = Joy_Y - pointer_Joystick->Yoffset;
  }
  
  if(Joy_X < 128){
    Joy_X = 128 - Joy_X;
    Joy_X = Joy_X * 100;
    Joy_X = Joy_X / 128;
    Res_X = (-1)*(Joy_X);
    }else{
    Joy_X = Joy_X - 128;
    Joy_X = Joy_X * 100;
    Joy_X = Joy_X / 128;
    Res_X = Joy_X;
  }
  
  if(Joy_Y < 128){
    Joy_Y = 128 - Joy_Y;
    Joy_Y = Joy_Y * 100;
    Joy_Y = Joy_Y / 128;
    Res_Y = (-1)*(Joy_Y);
    }else{
    Joy_Y = Joy_Y - 128;
    Joy_Y = Joy_Y * 100;
    Joy_Y = Joy_Y / 128;
    Res_Y = Joy_Y;
  }
  
  pointer_Joystick->PrevDir = pointer_Joystick->Dir;
  
  if(Res_X > THRS)
  {
    pointer_Joystick->Dir = Right;
  }
  else if (Res_X < THRS_NEG)
  {
    pointer_Joystick->Dir = Left;
  }
  else if (Res_Y > THRS)
  {
    pointer_Joystick->Dir = Up;
  }
  else if (Res_Y < THRS_NEG)
  {
    pointer_Joystick->Dir = Down;
  }
  else
  {
    pointer_Joystick->Dir = Neutral;
  }
  
  pointer_Joystick->Xpos = Res_X;
  pointer_Joystick->Ypos = Res_Y;
}

/***************************************************************************//**
 * @brief 	Prints the current position of the Joystick on the UART
 * @param   pointer_Joystick   pointer to Joystick which is used
 * @return 	None.
 * @date	  09.09.2013 
*******************************************************************************/
void Print_Joystick_Position(struct JoyStruct * pointer_Joystick)
{
  printf("\r\n---Joystick data---\r\n");
  printf("Joystick Xpos: %d%%\r\n",pointer_Joystick->Xpos);
  printf("Joystick Ypos: %d%%\r\n",pointer_Joystick->Ypos);
  switch (pointer_Joystick->Dir)
  {
    case 0:
      printf("Joystick Dir: Right\r\n");
  	  break;
    case 1:
      printf("Joystick Dir: Left\r\n");
      break;
    case 2:
      printf("Joystick Dir: Up\r\n");
      break;
    case 3:
      printf("Joystick Dir: Down\r\n");
      break;
    case 4:
      printf("Joystick Dir: Neutral\r\n");
      break;
    default:
      printf("MAAAADREES\r\n");
      break;      
  }    
}

/***************************************************************************//**
 * @brief 	Reads the position of the Sliders on the Multifunction Card
 * @param   pointer Sliders   pointer to Sliders which are used
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void Read_Sliders(struct SlideStruct * pointer_Sliders)
{
  unsigned int Slider_L;
  unsigned int Slider_R;
  Slider_L = (unsigned int)ADC_Read(SLIDER_LEFT);
  Slider_R = (unsigned int)ADC_Read(SLIDER_RIGHT);
  
  Slider_L = Slider_L * 100;
  Slider_L = Slider_L / 255;
  
  Slider_R = Slider_R * 100;
  Slider_R = Slider_R / 255;
  
  pointer_Sliders->LeftSlider = Slider_L;
  pointer_Sliders->RightSlider = Slider_R;
}

/***************************************************************************//**
 * @brief 	Prints current position of the sliders on the UART
 * @param   pointer Sliders   pointer to sliders which are used
 * @return 	None.
 * @date	  11.09.2013 
*******************************************************************************/
void Print_Sliders_Position(struct SlideStruct * pointer_Sliders)
{
  printf("\r\n---Sliders data---\r\n");
  printf("Slider Left: %d%%\r\n",pointer_Sliders->LeftSlider);
  printf("Slider Right: %d%%\r\n",pointer_Sliders->RightSlider);
}
