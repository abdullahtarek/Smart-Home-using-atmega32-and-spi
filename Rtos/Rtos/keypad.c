/*
 * keypad.c
 *
 * Created: 7/12/2018 3:24:21 PM
 *  Author: Abdullah
 */ 

#include <avr/io.h>



void keypad_init()
{
	DDRC = 0x0f;
	PORTC = 0xf0;
	//floating point
	SFIOR &=(~(1<<PUD));
}

char check()
{
	char ret =0;
	char flag=0;
	
	char buttonss[4][4]  = {{'7','4','1','o'},{'8','5','2','0'},{'9','6','3','='},{'//','*','-','+'}};
	
	char row,col;
	
	for(char r=0;r<4;r++)
	{
		PORTC |=0x0f;
		PORTC &= (~(1<<r));
		
		for(char c=0;c<4;c++)
		{
			if(((PINC& (1<<(c+4)))>>(c+4))==0)
			{
				row=c;
				col=r;
				flag=1;
				ret=1;
			}
			
		}
		if(flag == 1 )
		{
			break;
		}
	}
	
	if(flag==1)
	{
		ret = buttonss[row][col];
		
	}
	
	
	
	
	return ret;
}