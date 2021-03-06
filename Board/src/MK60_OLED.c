#include "MK60_OLED.h"
#include "MK60_gpio.h"
#include "include.h"

//======================================

const uint8 F6x8[][6] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};

uint8 ASCII[] =       
{  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0  
  0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1  
  0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2  
  0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3  
  0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4  
  0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5  
  0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6  
  0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7  
  0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8  
  0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9  
  0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10  
  0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14  
  0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15  
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16  
  0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17  
  0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18  
  0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19  
  0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20  
  0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21  
  0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22  
  0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23  
  0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24  
  0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25  
  0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26  
  0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27  
  0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28  
  0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29  
  0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30  
  0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31  
  0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32  
  0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33  
  0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34  
  0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35  
  0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36  
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37  
  0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38  
  0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39  
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40  
  0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41  
  0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42  
  0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43  
  0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44  
  0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45  
  0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46  
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47  
  0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48  
  0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49  
  0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50  
  0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51  
  0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52  
  0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53  
  0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54  
  0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55  
  0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56  
  0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57  
  0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58  
  0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59  
  0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60  
  0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61  
  0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62  
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63  
  0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64  
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65  
  0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66  
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67  
  0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68  
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69  
  0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70  
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71  
  0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72  
  0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73  
  0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74  
  0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75  
  0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76  
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77  
  0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78  
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79  
  0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80  
  0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81  
  0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82  
  0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83  
  0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84  
  0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85  
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86  
  0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87  
  0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88  
  0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89  
  0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90  
  0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91  
  0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92  
  0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93  
  0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94  
};  
uint8 photo2[][14]=
{
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC},
{0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0},
{0xC0,0xC0,0xC0,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFC,0xF0,0xE1,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x01,0x01,0x03,0x06,0x04,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF},
{0xFF,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x08,0x10,0x20,0x60,0xC0,0x80},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFE,0x10},
{0x00,0x00,0x00,0x00,0x80,0xC0,0x70,0x1C,0x06,0x03,0x06,0x0C,0x18,0x30},
{0x20,0x60,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0x84,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00},

};

unsigned char OLED_GRAM[128][8];  
void OLED_WRCMD(uint8 cmd)  
{  
    uint8 i=0;  
    gpio_set(OLED_DC,0);  
    for(i=0;i<8;i++)  
    {  
        gpio_set(OLED_SCL,0);  
        if(cmd&0x80) gpio_set(OLED_SDA,1);
        else         gpio_set(OLED_SDA,0);
        gpio_set(OLED_SCL,1);
        cmd<<=1;
}  
}  
void OLED_WRDATA(uint8 dat)   // 实现写入一字节数据
{
    uint8 i=0;
    gpio_set(OLED_DC,1);
    for(i=0;i<8;i++)
  {
        gpio_set(OLED_SCL,0);
         if(dat&0x80) gpio_set(OLED_SDA,1);
         else         gpio_set(OLED_SDA,0);
        gpio_set(OLED_SCL,1);  
        dat<<=1;  
  }    
}  
void OLED_Setxy(uint8 x, uint8 y)     //OLED 设置坐标  
{   
  OLED_WRCMD(0xb0+y);
  OLED_WRCMD(((x&0xf0)>>4)|0x10);
  OLED_WRCMD((x&0x0f)|0x01);
}   

void set_xy(uint8 x,uint8 y)
{
    //wr_oled( ( y|0xb0),0);
    OLED_WRCMD(y|0xb0);
    OLED_WRCMD(x&0x0f);
    OLED_WRCMD(((x&0xf0)>>4)|0x10);
    //wr_oled( ( x&0x0f),0);          //低四位
    //wr_oled( (((x&0xf0)>>4)|0x10),0); //得到高四位

}
void OLED_Fill(uint8 bmp_dat)   //bmp_dat=0x00全屏灭，bmp_dat=0xff全屏亮  
{  
   uint8 y,x;  
   for(y=0;y<8;y++)  
   {  
     OLED_WRCMD(0xb0+y);  
     OLED_WRCMD(0x01);  
     OLED_WRCMD(0x10);  
     for(x=0;x<X_WIDTH;x++)  
        OLED_WRDATA(bmp_dat);  
   }  
}  
void OLED_Init(void) //OLED初始化    
{    
   //SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;//使能PA时钟
  SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK;
     gpio_init(OLED_SCL,GPO,1);  
     gpio_init(OLED_DC,GPO,1);//初始化DC口  
     gpio_init(OLED_RST,GPO,1);//初始化RST  
     gpio_init(OLED_SDA,GPO,1);  
   gpio_set(OLED_SCL,1);  
   gpio_set(OLED_RST,0);  
   DELAY_MS(50);;  
     gpio_set(OLED_RST,1);       //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕     
   OLED_WRCMD(0xae);//--关闭显示                                         turn off oled panel  
   OLED_WRCMD(0x00);//---设置低列地址                                    set low column address  
   OLED_WRCMD(0x10);//---高列地址                                        set high column address      
   OLED_WRCMD(0x40);//--设置起始地址映射内存显示开始行（0x 00 ~ 0x3f）   set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)  
   OLED_WRCMD(0x81);//--设置对比度控制寄存器                             set contrast control register  
   OLED_WRCMD(0xcf); // 电流输出亮度设置赛格                             Set SEG Output Current Brightness  
   OLED_WRCMD(0xa1);//--设置赛格/列映射  0xa0左右反置0xa1正常            Set SEG/Column Mapping     0xa0左右反置 0xa1正常  
   OLED_WRCMD(0xc8);//设置网站/行扫描方向 0xc0上下反置 0xc8正常          Set COM/Row Scan Direction     
   OLED_WRCMD(0xa6);//--正常显示                                         set normal display  
   OLED_WRCMD(0xa8);//--集复用率（1 - 64）                               set multiplex ratio(1 to 64)  
   OLED_WRCMD(0x3f);//--1/64 duty  
   OLED_WRCMD(0xd3);//-设置显示偏移位移映射内存计数器（0x 00 ~ 0x3f）    set display offset  Shift Mapping RAM Counter (0x00~0x3F)  
   OLED_WRCMD(0x00);//-不偏移                                            not offset  
   OLED_WRCMD(0xd5);//--设置显示时钟的分频比/振荡器频率                  set display clock divide ratio/oscillator frequency  
   OLED_WRCMD(0x80);//--组分比，时钟设置为100帧/秒                       set divide ratio, Set Clock as 100 Frames/Sec  
   OLED_WRCMD(0xd9);//--设定充电周期                                     set pre-charge period  
   OLED_WRCMD(0xf1);//15集充电放电1钟钟表                                Set Pre-Charge as 15 Clocks & Discharge as 1 Clock  
   OLED_WRCMD(0xda);//--设置组件的引脚配置硬件                           set com pins hardware configuration  
   OLED_WRCMD(0x12);  
   OLED_WRCMD(0xdb);//--集vcomh                                          set vcomh  
   OLED_WRCMD(0x40);//威科姆取消水平集                                   Set VCOM Deselect Level  
   OLED_WRCMD(0x20);//-设置页面寻址模式（0x 00 /将/ 0x02）               Set Page Addressing Mode (0x00/0x01/0x02)  
   OLED_WRCMD(0x02);//  
   OLED_WRCMD(0x8d);//--充电泵启用/禁用                                  set Charge Pump enable/disable  
   OLED_WRCMD(0x14);//--集（0x 10个）禁用                                set(0x10) disable  
   OLED_WRCMD(0xa4);// 使整个显示（0xa4 / 0xa5）                         Disable Entire Display On (0xa4/0xa5)  
   OLED_WRCMD(0xa6);// 禁用反显示（0xa6 / 7）                            Disable Inverse Display On (0xa6/a7)   
   OLED_WRCMD(0xaf);//--打开面板                                         turn on oled panel  
   OLED_Fill(0x00);  //初始清屏  
   OLED_Setxy(0,0);   
}     
void OLED_6x8(uint8 x,uint8 y,uint8 ch[])//显示6*8一组标准ASCII字符串 显示的坐标（x,y），y为页范围0～7  
{  
   uint8 c=0,i=0,j=0;        
   while (ch[j]!='\0')  
   {      
     c =ch[j]-32;  
     if(x>126)  
        {x=0;y++;}  
     OLED_Setxy(x,y);      
     for(i=0;i<6;i++)       
       OLED_WRDATA(F6x8[c][i]);    
     x+=6;  
     j++;  
   }  
}  
void OLED_Cler_6x8(uint8 x,uint8 y,uint8 n)//清除N个6*8字符  
{  
   unsigned int i=0;  
   OLED_Setxy(x,y);  
   if(x>126)  
     {x=0;y++;}  
   for(i=0;i<6*n;i++)  
       OLED_WRDATA(0x00);  
}  


void LCD_ZI(uint8 x,uint8 y,uint8 ch) {

  uint8 c=0,i=0;
  c=ch-32;
  OLED_Setxy(x,y);
  for(i=0;i<6;i++)  {
    
    OLED_WRDATA(F6x8[c][i]);
  }
}

void LCD_SHUZI(uint8 x,uint8 y,int shu) {
  int qian,bai,shi,ge,i;
  int fushu = 0;
  if(shu < 0){
    shu = -1*shu;
    fushu = 1;
  }
  qian = shu /1000;
  bai  = (shu-qian*1000) /100;
  shi  = (shu-qian*1000-bai*100)/10;
  ge   = shu-qian*1000-bai*100-shi*10;
  
  set_xy(x,y);
  if(fushu){
    for(i=0;i<6;i++)  {
      OLED_WRDATA(F6x8[13][i]);
    }
  }else{
      for(i=0;i<6;i++)  {
      OLED_WRDATA(F6x8[qian+48-32][i]);
    }
  }
  set_xy(x+6,y);
 
    for(i=0;i<6;i++)  {
    
    OLED_WRDATA(F6x8[bai+48-32][i]);
  }
 
  set_xy(x+12,y);
  
    for(i=0;i<6;i++)  {
    
    OLED_WRDATA(F6x8[shi+48-32][i]);
  }
  
  set_xy(x+18,y);
  
    for(i=0;i<6;i++)  {
    
    OLED_WRDATA(F6x8[ge+48-32][i]);
  }

}
void OLED_8x16(uint8 x,uint8 y,uint8 ch[])//显示8*16一组标准ASCII字符串    显示的坐标（x,y），y为页范围0～7  
{  
  unsigned char c=0,i=0,j=0;  
  while (ch[j]!='\0')  
  {      
    c =ch[j]-32;  
    if(x>120)  
      {x=0;y+=2;}  
    OLED_Setxy(x,y);      
    for(i=0;i<8;i++)       
      OLED_WRDATA(ASCII[c*16+i]);  
    OLED_Setxy(x,y+1);      
    for(i=0;i<8;i++)       
      OLED_WRDATA(ASCII[c*16+i+8]);    
    x+=8;  
    j++;  
  }  
}  
void OLED_Cler_8x16(uint8 x,uint8 y,uint8 n) //清除n个8*16字符  
{  
    unsigned char i;  
    if(x>120)  
      {x=0;y++;}  
    OLED_Setxy(x,y);  
    for(i=0;i<8*n;i++)  
      OLED_WRDATA(0x00);  
    OLED_Setxy(x,y+1);  
    for(i=0;i<8*n;i++)  
      OLED_WRDATA(0x00);      
}  
/*void OLED_16x16(uint8 x,uint8 y,uint8 N)//显示16*16点阵  显示的坐标（x,y），y为页范围0～7  
{  
  unsigned char wm=0;  
  unsigned int adder=32*N;  //        
  OLED_Setxy(x , y);  
  for(wm = 0;wm < 16;wm++)  //               
  {  
    OLED_WRDATA(W16x16[adder]);   
    adder += 1;  
  }        
  OLED_Setxy(x,y + 1);   
  for(wm = 0;wm < 16;wm++) //           
  {  
    OLED_WRDATA(W16x16[adder]);  
    adder += 1;  
  }           
}  
void OLED_Cler_16x16(uint8 x,uint8 y, uint8 n)//清除n个16*16字  
{  
  unsigned char i=0;  
  OLED_Setxy(x,y);  
  for(i=0;i<16*n;i++)  
     OLED_WRDATA(0x00);  
  OLED_Setxy(x,y+1);  
  for(i=0;i<16*n;i++)  
     OLED_WRDATA(0x00);  
}  */
void Draw_BMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 BMP[])//显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*  
{     
 unsigned int j=0;  
 unsigned char x,y;  
    
  if(y1%8==0)  
     y=y1/8;        
  else   
     y=y1/8+1;  
  for(y=y0;y<y1;y++)  
  {  
     OLED_Setxy(x0,y);                
     for(x=x0;x<x1;x++)  
     {        
        OLED_WRDATA(BMP[j++]);            
     }  
  }  
}  
void OLED_Refresh_Gram(void)  
{  
    uint8 ii,nn;  
    for(ii=2;ii<8;ii++)  
    {  
        OLED_WRCMD(0xb0+ii);  
        OLED_WRCMD(0x00);  
        OLED_WRCMD(0x10);  
        for(nn=0;nn<128;nn++)OLED_WRDATA(OLED_GRAM[nn][ii]);  
 }  
}  
void OLED_DRAWPoint(uint8 x,uint8 y,uint8 t)  

{  
  
    uint8 pos,bx,temp=0;  
    if(x>127||y>63)return;  
    pos=7-y/8;  
    bx=y%8;  
    temp=1<<(7-bx);  
    if(t)OLED_GRAM[x][pos]|=temp;
    else OLED_GRAM[x][pos]&=~temp;
    
}  

void DrawLine(uint8 num)
{
  OLED_DRAWPoint(2,num,1);
  OLED_Refresh_Gram();
  uint8 row,col;
for(row=126;row>0;row--)
{
for(col=0;col<8;col++)
OLED_GRAM[row+1][col]=OLED_GRAM[row][col];
 }  
}

void DrawPixel(uint8 Pixel[]){
  uint8 temp;
  for(int i = 127; i >= 0; i--){
    temp = Pixel[i];
    for(int j = 16; j < 64; j++){
      if(j-8 > (int)(temp>>2)){
        OLED_DRAWPoint(i,j,0);
      }
      else{
        OLED_DRAWPoint(i,j,1);
      }
    }
  }
  OLED_Refresh_Gram();
}



void LCD__change_num(unsigned char x, unsigned char y,float float_num) 
{
  unsigned char i = 0;
  unsigned char range_flag = 0;
  unsigned long long_num=1;
  unsigned char float_numchar[6] = "3.141"; 
  unsigned char sign_flag = 0;
  if(float_num < 0)
  {
        sign_flag = 1;
        float_num = 0 - float_num;
  }
  if(float_num >= 10000000){range_flag = 0;} 
  else if(float_num >= 1000000){range_flag = 1;}
  else if(float_num >= 100000){range_flag = 2;}
  else if(float_num >= 10000){range_flag = 3;}
  else if(float_num >= 1000){range_flag = 4;}
  else if(float_num >= 100){range_flag = 5;}
  else if(float_num >= 10){range_flag = 6;}
  else if((float_num >= 1) || (float_num == 0)){range_flag = 7;}
  else if(float_num >= 0.1){range_flag = 8;}
  else if(float_num >= 0.01){range_flag = 9;}
  else if(float_num >= 0.001){range_flag = 10;}
  else if(float_num >= 0.0001){range_flag = 11;}

  switch (range_flag) 
  {
    default : break;
    case 3 : long_num = (unsigned long)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = (long_num/10000000)+'0';
          long_num = long_num%10000000; break;
          case 1 : float_numchar[i] = (long_num/1000000)+'0';
          long_num = long_num%1000000; break;
          case 2 : float_numchar[i] = (long_num/100000)+'0';
          long_num = long_num%100000; break;          
          case 3 : float_numchar[i] = (long_num/10000)+'0';
          long_num = long_num%10000; break;
          case 4 : float_numchar[i] = (long_num/1000)+'0'; 
          long_num = long_num%1000; break;                             
        } 
      }break;
    case 4 : long_num = (unsigned long)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = (long_num/1000000)+'0';
          long_num = long_num%1000000; break;
          case 1 : float_numchar[i] = (long_num/100000)+'0';
          long_num = long_num%100000; break;
          case 2 : float_numchar[i] = (long_num/10000)+'0';
          long_num = long_num%10000; break;          
          case 3 : float_numchar[i] = (long_num/1000)+'0';
          long_num = long_num%1000; break;
          case 4 : float_numchar[i] = ' '; break;                              
        } 
      }break;
    case 5 : long_num = (unsigned long)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = (long_num/100000)+'0';
          long_num = long_num%100000; break;
          case 1 : float_numchar[i] = (long_num/10000)+'0';
          long_num = long_num%10000; break;
          case 2 : float_numchar[i] = (long_num/1000)+'0';
          long_num = long_num%1000; break;
          case 3 : float_numchar[i] = '.'; break;
          case 4 : float_numchar[i] = (long_num/100)+'0';
          long_num = long_num%100; break;                            
        } 
      }break;    
    case 6 : long_num = (unsigned long)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] =  (long_num/10000)+'0';
          long_num = long_num%10000; break;
          case 1 : float_numchar[i] =  (long_num/1000)+'0';
          long_num = long_num%1000; break;
          case 2 : float_numchar[i] = '.'; break;
          case 3 : float_numchar[i] =  (long_num/100)+'0';
          long_num = long_num%100; break;
          case 4 : float_numchar[i] =  (long_num/10)+'0';
          long_num = long_num%10; break;                             
        } 
      }break;
    case 7 : long_num = (unsigned long)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] =  (long_num/1000)+'0';
          long_num = long_num%1000; break;
          case 1 : float_numchar[i] = '.'; break;
          case 2 : float_numchar[i] =  (long_num/100)+'0';
          long_num = long_num%100; break;          
          case 3 : float_numchar[i] =  (long_num/10)+'0';
          long_num = long_num%10; break;
          case 4 : float_numchar[i] =  (long_num)+'0'; break;                              
        } 
      }break; 
    case 8 : long_num = (unsigned int)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = '0'; break;
          case 1 : float_numchar[i] = '.'; break;
          case 2 : float_numchar[i] = (long_num/100)+'0';
          long_num = long_num%100; break;          
          case 3 : float_numchar[i] = (long_num/10)+'0';
          long_num = long_num%10; break;
          case 4 : float_numchar[i] = (long_num)+'0'; break;                             
        } 
      }break;
    case 9 : long_num = (unsigned int)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = '0'; break;
          case 1 : float_numchar[i] = '.'; break;
          case 2 : float_numchar[i] = '0'; break;          
          case 3 : float_numchar[i] = (long_num/10)+'0';
          long_num = long_num%10; break;
          case 4 : float_numchar[i] = (long_num)+'0'; break;                           
        } 
      }break;
    case 10 : long_num = (unsigned int)(float_num*1000);
      for(i=0;i<5;i++) 
      {
        switch (i)
        {
          default : break;
          case 0 : float_numchar[i] = '0'; break;
          case 1 : float_numchar[i] = '.'; break;
          case 2 : float_numchar[i] = '0'; break; 
          case 3 : float_numchar[i] = '0'; break;         
          case 4 : float_numchar[i] = (long_num)+'0'; break;                          
        } 
      }break;
  }
  if(sign_flag){float_numchar[4] = 94;}
  float_numchar[5] = 0;
  OLED_6x8(x, y, float_numchar);

}




/*void OLED_Display()
{
     
              //DrawPixel(Pixel);
  
              LCD_SHUZI(0,0,Linedev[0]); 
              LCD_SHUZI(30,0,Bl[0]);
              LCD_SHUZI(60,0,Br[0]);
              LCD_SHUZI(90,0,Recognition_Mid[0]);
              
      
              //电机闭环结果
              OLED_6x8(0,3,"dev"); LCD_SHUZI(80,3,distance_dev);
              OLED_6x8(0,4,"Sp_Ln "); LCD_SHUZI(80,4,SpeedLeNow);
              OLED_6x8(0,5,"SP_Rn"); LCD_SHUZI(80,5,SpeedRiNow);
              //OLED_6x8(0,4,"dis_dev"); LCD_SHUZI(80,4,distance_dev);

              
     
              //OLED_6x8(0,3,"s_flag"); LCD_SHUZI(80,3,stop_flag);
              
              
              
             // OLED_6x8(0,1,"DjD:"); LCD__change_num(80,1,Speed_Derivative);
              //OLED_6x8(0,2,"DjP:"); LCD__change_num(80,2,Speed_Proportion);
              //OLED_6x8(0,3,"DjI:"); LCD__change_num(80,3,Speed_Integral);
              
              
              
              //舵机PD
              OLED_6x8(0,1,"DD:"); LCD__change_num(80,1,Servo_Derivative);
              OLED_6x8(0,2,"DP:"); LCD__change_num(80,2,Servo_Proportion); 
              //OLED_6x8(0,4,"zx:"); LCD__change_num(80,4,Recognition_Mid[1]);
              //OLED_6x8(0,5,"zx1:"); LCD__change_num(80,5,Recognition_Mid[2]);  
              OLED_6x8(0,6,"Spd_Want"); LCD_SHUZI(80,6,Speed_Want);

              OLED_6x8(0,7,"dis"); LCD__change_num(80,7,distance[0]);
     
}*/

/*!
 *  @brief      显示小数（0.001~9999.999）
 */
void OLED_xiaoshu(uint8 x,uint8 y,float shu)//显示小数,x y为坐标
{
    int qian,bai,shi,ge,hao,fen,li,i;//设置各位变量
    int fushu = 0;
    int num = (int)floor(shu * 1000);//保留三位小数，并把原变量化为整形
  if(shu < 0)//判断是否为负数
  {
    num = -1*num;
    fushu = 1;
  }
  qian = num /1000000;
  bai  = (num-qian*1000000) /100000;
  shi  = (num-qian*1000000-bai*100000)/10000;
  ge   = (num-qian*1000000-bai*100000-shi*10000)/1000;
  hao =  (num-qian*1000000-bai*100000-shi*10000-ge*1000)/100;
  fen = (num-qian*1000000-bai*100000-shi*10000-ge*1000-hao*100)/10;
  li = num-qian*1000000-bai*100000-shi*10000-ge*1000-hao*100-fen*10;        //分离各位
  
  set_xy(x,y);  //设置坐标
  if(fushu)//显示负号
  {
    for(i=0;i<6;i++)  
    {
      OLED_WRDATA(F6x8[13][i]);
    }
  }
  else
  {
      for(i=0;i<6;i++)  
      {
      OLED_WRDATA(F6x8[qian+48-32][i]);
      }
  }
  set_xy(x+6,y);
 
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[bai+48-32][i]);
    }
 
  set_xy(x+12,y);
  
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[shi+48-32][i]);
    }
  
  set_xy(x+18,y);
  
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[ge+48-32][i]);
    }
  set_xy(x+24,y);
   for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[14][i]);//显示小数点
    }
   set_xy(x+30,y);
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[hao+48-32][i]);
    } 
   set_xy(x+36,y);
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[fen+48-32][i]);
    }
    set_xy(x+42,y);
    for(i=0;i<6;i++)  
    {
    
    OLED_WRDATA(F6x8[li+48-32][i]);
    }
}


void Oled_Menu_init()  //OLED菜单初始化
{
      OLED_Init();
      key_init (KEY_U); 
      key_init (KEY_D); 
      key_init (KEY_L); 
      key_init (KEY_R);
      key_init (KEY_A); 
}

void Display_Page1(float* num)  //显示第一页
{
    OLED_6x8(30,0,"M E N U");
    OLED_6x8(0,1,"distance_p");
    OLED_6x8(0,2,"distance_I");
    OLED_6x8(0,3,"distance_D");
    OLED_6x8(0,4,"distance");
    OLED_6x8(0,5,"motor_P");
    OLED_6x8(0,6,"motor_I");
    OLED_6x8(0,7,"motor_D");
    OLED_xiaoshu(75,1,num[0]);
    OLED_xiaoshu(75,2,num[1]);
    OLED_xiaoshu(75,3,num[2]);
    OLED_xiaoshu(75,4,num[3]);
    OLED_xiaoshu(75,5,num[4]);
    OLED_xiaoshu(75,6,num[5]);
    OLED_xiaoshu(75,7,num[6]);
}

void Display_Page2(float* num)   //显示第二页
{
    OLED_6x8(30,0,"M E N U");
    OLED_6x8(0,1,"test_P");
    OLED_6x8(0,2,"test_I");
    OLED_6x8(0,3,"test_D");
    OLED_xiaoshu(75,1,num[7]);
    OLED_xiaoshu(75,2,num[8]);
    OLED_xiaoshu(75,3,num[9]);
}

void Display_Jinzhi1(float* num)   //显示进制第一页
{
    OLED_6x8(30,0,"Jin Zhi");
    OLED_6x8(0,1,"distance_p");
    OLED_6x8(0,2,"distance_I");
    OLED_6x8(0,3,"distance_D");
    OLED_6x8(0,4,"distance");
    OLED_6x8(0,5,"motor_P");
    OLED_6x8(0,6,"motor_I");
    OLED_6x8(0,7,"motor_D");
    OLED_xiaoshu(75,1,num[0]);
    OLED_xiaoshu(75,2,num[1]);
    OLED_xiaoshu(75,3,num[2]);
    OLED_xiaoshu(75,4,num[3]);
    OLED_xiaoshu(75,5,num[4]);
    OLED_xiaoshu(75,6,num[5]);
    OLED_xiaoshu(75,7,num[6]);
}

void Display_Jinzhi2(float* num)   //显示进制第二页
{
    OLED_6x8(30,0,"Jin Zhi");
    OLED_6x8(0,1,"test_P");
    OLED_6x8(0,2,"test_I");
    OLED_6x8(0,3,"test_D");
    OLED_xiaoshu(75,1,num[7]);
    OLED_xiaoshu(75,2,num[8]);
    OLED_xiaoshu(75,3,num[9]);
}

float Set_jinzhi(float num)   //更改进制
{
 if(num<0)
 {
  num=-num;
 }
int a=0;
if(num<=0.03&&num>=0) a=1;
else if(num<=0.3&&num>0.03) a=2;
else if(num<=3&&num>0.3) a=3;
else if(num<=30&&num>3) a=4;
else if(num<=300&&num>30) a=5;
else if(num<=3000&&num>300) a=6;
else if(num>3000) a=7;
float jinzhi;
switch(a)
{
case 1:jinzhi=0.001;break;
case 2:jinzhi=0.01; break;
case 3:jinzhi=0.1;  break;
case 4:jinzhi=1;    break;
case 5:jinzhi=10;   break;
case 6:jinzhi=100;  break;
case 7:jinzhi=1000; break;
}
return jinzhi;
}


void Menu_Change_Data(float* num,float* Jinzhi)    //设定坐标，更改数据
{
  uint8 static y=1,flag=0,sign=0,mark=0; //y表示纵坐标，flag判断确认开关是否按下，sign判断翻页,mark判断是否更改进制
    if(key_check(KEY_B) ==  KEY_DOWN)
    {
      mark=~mark;
      if(mark)
      {
      Display_Jinzhi1(Jinzhi);
      }
      if(!mark)
      {
      Display_Page1(num);
      }
    }
if(mark)
{
     if(key_check(KEY_U) ==  KEY_DOWN)
       {
        flag=0;
        OLED_6x8(67,y," "); 
        y++;
        if(y==8)
        {
          OLED_Fill(0x00);
          Display_Jinzhi2(Jinzhi);
          sign=1;
          y=1;
        }
        OLED_6x8(67,y,"*");
       }
      
     if(key_check(KEY_D) ==  KEY_DOWN)
     {
       flag=0;
       OLED_6x8(67,y," "); 
        y-- ;  
        if(y==0)
        {
          OLED_Fill(0x00);
          Display_Jinzhi1(Jinzhi);
          sign=0;
          y=7;
        }
        OLED_6x8(67,y,"*");
     }

     if(key_check(KEY_A) ==  KEY_DOWN) //确认键
     {
       flag=1;
     }
    
     if(key_check(KEY_R) ==  KEY_DOWN && flag==1)
     {
         if(sign==0)
         {
          Jinzhi[y-1]-=0.5;
          DELAY_MS(100);     //延时
         }
         if(sign==1)
         {
          Jinzhi[y+6]-=0.5;
          DELAY_MS(100);    
         }
       }
    
     if(key_check(KEY_L) ==  KEY_DOWN && flag==1)
     {
         if(sign==0)
         {
          Jinzhi[y-1]+=0.5;
          DELAY_MS(100);
         }
         if(sign==1)
         {
          Jinzhi[y+6]+=0.5;
           DELAY_MS(100); 
         }
       }
    
    if(sign==0)          //刷新
    {
        Display_Jinzhi1(Jinzhi);
    }
    if(sign==1)
    {
        Display_Page2(Jinzhi);
    }
}


if(!mark)
{      
    if(key_check(KEY_U) ==  KEY_DOWN)
       {
        flag=0;
        OLED_6x8(67,y," "); 
        y++;
        if(y==8)
        {
          OLED_Fill(0x00);
          Display_Page2(num);
          sign=1;
          y=1;
        }
        OLED_6x8(67,y,"*");
       }
      
     if(key_check(KEY_D) ==  KEY_DOWN)
     {
       flag=0;
       OLED_6x8(67,y," "); 
        y-- ;  
        if(y==0)
        {
          OLED_Fill(0x00);
          Display_Page1(num);
          sign=0;
          y=7;
        }
        OLED_6x8(67,y,"*");
     }

     if(key_check(KEY_A) ==  KEY_DOWN) //确认键
     {
       flag=1;
     }
    
     if(key_check(KEY_R) ==  KEY_DOWN && flag==1)
     {
         if(sign==0)
         {
          num[y-1]=num[y-1]-Jinzhi[y-1];
          DELAY_MS(100);     //延时
         }
         if(sign==1)
         {
          num[y+6]=num[y+6]-Jinzhi[y+6];
          DELAY_MS(100);    
         }
       }
    
     if(key_check(KEY_L) ==  KEY_DOWN && flag==1)
     {
         if(sign==0)
         {
          num[y-1]=num[y-1]+Jinzhi[y-1];
          DELAY_MS(100);
         }
         if(sign==1)
         {
          num[y+6]=num[y+6]+Jinzhi[y+6];
           DELAY_MS(100); 
         }
       }
    
    if(sign==0)          //刷新
    {
        Display_Page1(num);
    }
    if(sign==1)
    {
        Display_Page2(num);
    }
}    
    
 }
void OLED_WRDATA_Yinyang(uint8 dat,uint8 type)   // 实现正反码写入一字节数据
{
    uint8 i=0;
    if(type == 1)
    {
        dat = ~dat;
    }
    gpio_set(OLED_DC,1);
    for(i=0;i<8;i++)
  {
        gpio_set(OLED_SCL,0);
         if(dat&0x80) gpio_set(OLED_SDA,1);
         else         gpio_set(OLED_SDA,0);
        gpio_set(OLED_SCL,1);  
        dat<<=1;  
  }
}  
  void OLED_Yinyangma_6x8 (uint8 x,uint8 y,uint8 type,uint8 ch[])//6*8阴阳码输出,tye=1亮字，type=0亮底
{  
   uint8 c=0,i=0,j=0;        
   while (ch[j]!='\0')  
   {      
     c =ch[j]-32;  
     if(x>126)  
        {x=0;y++;}  
     OLED_Setxy(x,y);      
     for(i=0;i<6;i++)       
       OLED_WRDATA_Yinyang(F6x8[c][i],type);    
     x+=6;  
     j++;  
   }  
}