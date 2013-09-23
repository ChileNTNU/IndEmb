﻿/***************************************************************************//**
 *   @file   font_5x7.c
 *   @brief  Font table
 *	 @date	 23.09.2013
 *   @author Tobias Franzen and Emilio Garcia
*******************************************************************************/

#include <avr/pgmspace.h>

//The index of this table corresponds to the ascii table but subtracting 32.
const char PROGMEM myfont[96][5] = {
  {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //0
  {0b00000000,0b00000000,0b01011110,0b00000000,0b00000000}, //1  !
  {0b00000000,0b00001110,0b00000000,0b00001110,0b00000000}, //2  "
  {0b00101000,0b01111100,0b00101000,0b01111100,0b00101000}, //3  #
  {0b00001000,0b01010100,0b01111100,0b01010100,0b00100000}, //4  $
  {0b00100110,0b00010000,0b00001000,0b01100100,0b00000000}, //5  %
  {0b00101000,0b01010100,0b00101000,0b01000000,0b00000000}, //6  &
  {0b00000000,0b00000000,0b00001110,0b00000000,0b00000000}, //7  '
  {0b00000000,0b00111100,0b01000010,0b00000000,0b00000000}, //8  (
  {0b00000000,0b01000010,0b00111100,0b00000000,0b00000000}, //9  )
  {0b00000000,0b01010100,0b00111000,0b01010100,0b00000000}, //10 *
  {0b00010000,0b00010000,0b01111100,0b00010000,0b00010000}, //11 +
  {0b00000000,0b10000000,0b01100000,0b00100000,0b00000000}, //12 ,
  {0b00010000,0b00010000,0b00010000,0b00010000,0b00000000}, //13 -
  {0b00000000,0b01100000,0b01100000,0b00000000,0b00000000}, //14 .
  {0b00100000,0b00010000,0b00001000,0b00000100,0b00000000}, //15 /
  {0b00000000,0b00111100,0b01000010,0b00111100,0b00000000}, //16 0
  {0b00000000,0b01000100,0b01111110,0b01000000,0b00000000}, //17 1
  {0b01000100,0b01100010,0b01010010,0b01001100,0b00000000}, //18 2
  {0b00100010,0b01001010,0b01001010,0b00110110,0b00000000}, //19 3
  {0b00011000,0b00010100,0b01111110,0b00010000,0b00000000}, //20 4
  {0b00101110,0b01001010,0b01001010,0b00110010,0b00000000}, // 5
  {0b00111100,0b01001010,0b01001010,0b00110000,0b00000000}, // 6
  {0b00000010,0b01100010,0b00011010,0b00000110,0b00000000}, // 7
  {0b00110100,0b01001010,0b01001010,0b00110100,0b00000000}, // 8
  {0b00001100,0b01010010,0b01010010,0b00111100,0b00000000}, // 9
  {0b00000000,0b01101100,0b01101100,0b00000000,0b00000000}, // :
  {0b10000000,0b01101100,0b00101100,0b00000000,0b00000000}, // ;
  {0b00000000,0b00010000,0b00101000,0b01000100,0b00000000}, // <
  {0b00101000,0b00101000,0b00101000,0b00101000,0b00000000}, // =
  {0b00000000,0b01000100,0b00101000,0b00010000,0b00000000}, // >
  {0b00000000,0b00000100,0b01010010,0b00001100,0b00000000}, // ?
  {0b00111100,0b01000010,0b01011010,0b00011100,0b00000000}, // @
  {0b01111100,0b00010010,0b00010010,0b01111100,0b00000000}, // A
  {0b01111110,0b01001010,0b01001010,0b00110100,0b00000000}, // B
  {0b00111100,0b01000010,0b01000010,0b00100100,0b00000000}, // C
  {0b01111110,0b01000010,0b01000010,0b00111100,0b00000000}, // D
  {0b01111110,0b01001010,0b01001010,0b01000010,0b00000000}, // E
  {0b01111110,0b00001010,0b00001010,0b00000010,0b00000000}, // F
  {0b00111100,0b01000010,0b01010010,0b01110100,0b00000000}, // G
  {0b01111110,0b00001000,0b00001000,0b01111110,0b00000000}, // H
  {0b00000000,0b01000010,0b01111110,0b01000010,0b00000000}, // I
  {0b00100000,0b01000000,0b01000000,0b00111110,0b00000000}, // J
  {0b01111110,0b00011000,0b00100100,0b01000010,0b00000000}, // K
  {0b01111110,0b01000000,0b01000000,0b01000000,0b00000000}, // L
  {0b01111110,0b00001100,0b00001100,0b01111110,0b00000000}, // M
  {0b01111110,0b00001100,0b00110000,0b01111110,0b00000000}, // N
  {0b00111100,0b01000010,0b01000010,0b00111100,0b00000000}, // O
  {0b01111110,0b00010010,0b00010010,0b00001100,0b00000000}, // P
  {0b00111100,0b01100010,0b01000010,0b10111100,0b00000000}, // Q
  {0b01111110,0b00010010,0b00110010,0b01001100,0b00000000}, // R
  {0b00100100,0b01001010,0b01010010,0b00100100,0b00000000}, // S
  {0b00000000,0b00000010,0b01111110,0b00000010,0b00000000}, // T
  {0b00111110,0b01000000,0b01000000,0b00111110,0b00000000}, // U
  {0b00011110,0b01100000,0b01100000,0b00011110,0b00000000}, // V
  {0b01111110,0b00110000,0b00110000,0b01111110,0b00000000}, // W
  {0b01100110,0b00011000,0b00011000,0b01100110,0b00000000}, // X
  {0b00000000,0b00001110,0b01110000,0b00001110,0b00000000}, // Y
  {0b01100010,0b01010010,0b01001010,0b01000110,0b00000000}, // Z
  {0b00000000,0b01111110,0b01000010,0b01000010,0b00000000}, // [
  {0b00000100,0b00001000,0b00010000,0b00100000,0b00000000}, // "\"
  {0b00000000,0b01000010,0b01000010,0b01111110,0b00000000}, // ]
  {0b00000000,0b00000100,0b00000010,0b00000100,0b00000000}, // ^
  {0b01000000,0b01000000,0b01000000,0b01000000,0b00000000}, // _
  {0b00000000,0b00000010,0b00000100,0b00000000,0b00000000}, // `
  {0b00110000,0b01001000,0b00101000,0b01111000,0b00000000}, // a
  {0b01111110,0b01001000,0b01001000,0b00110000,0b00000000}, // b
  {0b00110000,0b01001000,0b01001000,0b00000000,0b00000000}, // c
  {0b00110000,0b01001000,0b01001000,0b01111110,0b00000000}, // d
  {0b00110000,0b01101000,0b01011000,0b00010000,0b00000000}, // e
  {0b00010000,0b01111100,0b00010010,0b00000100,0b00000000}, // f
  {0b01010000,0b10101000,0b10101000,0b10011000,0b00000000}, // g
  {0b01111110,0b00001000,0b00001000,0b01110000,0b00000000}, // h
  {0b00000000,0b01001000,0b01111010,0b01000000,0b00000000}, // i
  {0b00000000,0b01000000,0b10000000,0b01111010,0b00000000}, // j
  {0b01111110,0b00010000,0b00101000,0b01000000,0b00000000}, // k
  {0b00000000,0b01000010,0b01111110,0b01000000,0b00000000}, // l
  {0b01111000,0b00010000,0b00011000,0b01110000,0b00000000}, // m
  {0b01111000,0b00001000,0b00001000,0b01110000,0b00000000}, // n
  {0b00110000,0b01001000,0b01001000,0b00110000,0b00000000}, // o
  {0b11111000,0b01001000,0b01001000,0b00110000,0b00000000}, // p
  {0b00110000,0b01001000,0b01001000,0b11111000,0b00000000}, // q
  {0b01111000,0b00001000,0b00001000,0b00010000,0b00000000}, // r
  {0b01010000,0b01011000,0b01101000,0b00101000,0b00000000}, // s
  {0b00001000,0b00111110,0b01001000,0b01000000,0b00000000}, // t
  {0b00111000,0b01000000,0b01000000,0b01111000,0b00000000}, // u
  {0b00000000,0b00111000,0b01000000,0b00111000,0b00000000}, // v
  {0b01111000,0b01100000,0b01100000,0b01111000,0b00000000}, // w
  {0b01001000,0b00110000,0b00110000,0b01001000,0b00000000}, // x
  {0b00011000,0b10100000,0b01000000,0b00111000,0b00000000}, // y
  {0b01001000,0b01101000,0b01011000,0b01001000,0b00000000}, // z
  {0b00000000,0b00001000,0b00111100,0b01000010,0b00000000}, // {
  {0b00000000,0b00000000,0b01111110,0b00000000,0b00000000}, // |
  {0b00000000,0b01000010,0b00111100,0b00001000,0b00000000}, // }
  {0b00000100,0b00000010,0b00000100,0b00000010,0b00000000}, // ~
  {0b00110000,0b01000110,0b01000000,0b01000110,0b00110000}
};

