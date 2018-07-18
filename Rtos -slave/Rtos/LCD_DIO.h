/*
 * LCD_DIO.h
 *
 * Created: 5/5/2018 9:51:06 AM
 *  Author: Abdullah
 */ 


#ifndef LCD_DIO_H_
#define LCD_DIO_H_
#include "LCD_config.h"

#define CLEAR_SCREEN 0x01
#define CURSOR_ON 0x0e

#if defined (LCD_8bit)

#define BIT_8_MODE 0x38
#define EN 0
#define RW 1
#define RS 2

#endif
#if defined (LCD_4bit)

#define EN 3
#define RW 2
#define RS 1

#endif


static void sendFallingEdge();
void LCD_vsendCommand(char cmd);
void LCD_vsendData(char data);
void LCD_VsnedString(char str[]);
void LCD_VINIT();


#endif /* LCD_DIO_H_ */