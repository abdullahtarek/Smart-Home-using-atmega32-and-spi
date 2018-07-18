/*
 * LCD_DIO.c
 *
 * Created: 5/5/2018 9:51:19 AM
 *  Author: Abdullah
 */ 
#include <avr/io.h>
#include "LCD_DIO.h"
#define F_CPU 8000000ul
#include <util/delay.h>





//LCD WRITES ONCE THERE IS FALLING EDGE ON EN PIN

#if defined (LCD_8bit)
void LCD_vsendCommand(char cmd) // run command on LCD
{
	PORTD =cmd; // the data
	PORTB&= (~(1<<RS)); // make RS regiter to zero to make it command
	sendFallingEdge(); // run the command
}
void LCD_vsendData(char data) // run command on LCD
{
	PORTD = data; // the data
	PORTB|= (1<<RS); // make RS regiter to zero to make it command
	sendFallingEdge(); // run the command
}
void LCD_VINIT()
{
	DDRD= 0xff;
	DDRB|=0x07;
	PORTB &=(~(1<<RW));
	
	LCD_vsendCommand(BIT_8_MODE);//8bit mode all 8 bits used for data
	LCD_vsendCommand(CLEAR_SCREEN);//clear screen
	LCD_vsendCommand(CURSOR_ON);//Turn on cursor
	_delay_ms(20);
	
}
#endif

#if defined (LCD_4bit)
void LCD_vsendCommand(char cmd) // run command on LCD
{
	PORTA&= (~(1<<RS));// make RS regiter to zero to make it command
	
	PORTA&=0x0f;
	
	PORTA |= (0xf0 & cmd);
	sendFallingEdge(); // run the command
	
	PORTA&=0x0f;
	PORTA |= ((0x0f &cmd)<<4);
	sendFallingEdge();// run the command
	
	
}
void LCD_VINIT()
{
	DDRA |= 0xf0;
	DDRA |=0x0e;
	PORTA &=(~(1<<RW));
	
	//4bit mode all 8 bits used for data
	LCD_vsendCommand(0x33);
	LCD_vsendCommand(0x32);
	LCD_vsendCommand(0x28); // 2 lines 4 bit mode
	
	LCD_vsendCommand(CLEAR_SCREEN);//clear screen
	LCD_vsendCommand(CURSOR_ON);//Turn on cursor
	_delay_ms(20);
	
}
void LCD_vsendData(char data) // run command on LCD
{
	PORTA|= (1<<RS); // make RS regiter to zero to make it command
	
	PORTA&=0x0f;
	
	PORTA |= (0xf0 & data);
	sendFallingEdge(); // run the command
	
	PORTA&=0x0f;
	PORTA |= ((0x0f &data)<<4);
	sendFallingEdge();// run the command
	
	
}
#endif
void clear_screen()
{
	LCD_vsendCommand(CLEAR_SCREEN);//clear screen
}
void LCD_VGOTO(char row,char col)
{
	char address;
	if (row==0)
	{
		address=0x80;
	}
	else
	{
		address=0xC0;
	}
	
	address +=col;
	
	LCD_vsendCommand(address);
	
}
static void sendFallingEdge()
{
	PORTA |=(1<<EN);
	_delay_ms(2);
	PORTA &=(~(1<<EN));
	_delay_ms(2);
}
void LCD_VsnedString(char str[])
{
	char i=0;
	while(str[i] != '\0')
	{
		LCD_vsendData(str[i]);
		i++;
	}
	
}

void writeSetpassword()
{
	LCD_vsendData('S');
	LCD_vsendData('e');
	LCD_vsendData('t');
	LCD_vsendData(' ');
	LCD_vsendData('P');
	LCD_vsendData('a');
	LCD_vsendData('s');
	LCD_vsendData('s');
	LCD_vsendData('w');
	LCD_vsendData('o');
	LCD_vsendData('r');
	LCD_vsendData('d');
	
}

void writeloginscreen()
{
	
	LCD_vsendData('L');
	LCD_vsendData('o');
	LCD_vsendData('g');
	LCD_vsendData('i');
	LCD_vsendData('n');
	LCD_vsendData(':');
	LCD_VGOTO(1,0);
	LCD_vsendData('1');
	LCD_vsendData('.');
	LCD_vsendData('A');
	LCD_vsendData('d');
	LCD_vsendData('m');
	LCD_vsendData('i');
	LCD_vsendData('n');
	LCD_vsendData(' ');
	LCD_vsendData('2');
	LCD_vsendData('.');
	LCD_vsendData('G');
	LCD_vsendData('u');
	LCD_vsendData('e');
	LCD_vsendData('s');
	LCD_vsendData('t');
}

void writewrongpassword()
{
	LCD_vsendData('W');
	LCD_vsendData('r');
	LCD_vsendData('o');
	LCD_vsendData('n');
	LCD_vsendData('g');
	LCD_vsendData(' ');
	LCD_vsendData('P');
	LCD_vsendData('a');
	LCD_vsendData('s');
	LCD_vsendData('s');
	LCD_vsendData('w');
	LCD_vsendData('o');
	LCD_vsendData('r');
	LCD_vsendData('d');
	
	
	
}

void writeadminscreen()
{
	
	LCD_vsendData('R');
	LCD_vsendData('o');
	LCD_vsendData('o');
	LCD_vsendData('m');
	LCD_vsendData('s');
	LCD_vsendData(':');
	LCD_vsendData('1');
	LCD_vsendData(' ');
	LCD_vsendData('2');
	LCD_vsendData(' ');
	LCD_vsendData('3');
	
	LCD_VGOTO(1,0);
	LCD_vsendData('4');
	LCD_vsendData('.');
	LCD_vsendData('T');
	LCD_vsendData('V');
	LCD_vsendData(' ');
	LCD_vsendData('5');
	LCD_vsendData('.');
	LCD_vsendData('A');
	LCD_vsendData('c');
	
	
	
	
	//LCD_vsendData('W');
	
	
}

void writeguestscreen()
{
	
	LCD_vsendData('R');
	LCD_vsendData('o');
	LCD_vsendData('o');
	LCD_vsendData('m');
	LCD_vsendData('s');
	LCD_vsendData(':');
	LCD_vsendData('1');
	LCD_vsendData(' ');
	LCD_vsendData('2');
	LCD_vsendData(' ');
	LCD_vsendData('3');
	
	
	
}