/*
 * Rtos.c
 *
 * Created: 6/1/2018 12:46:43 PM
 *  Author: Abdullah
 */ 


#include <avr/io.h>
#include "FreeRTOS.h"

#define F_CPU 8000000ul
#include <util/delay.h>
#include <avr/interrupt.h>
#include "task.h"
#include "eeprom.h"
#include "LCD_DIO.h"
#include "ADC.h"

TaskHandle_t task1handel = NULL;


void task1(void *ptr);
short xx;



int main(void)
{
	sei();
	adc_init();
	SPI_SlaveInit();
	
	DDRC |=(1<<7);
	DDRC |=(1<<6);
	DDRC |=(1<<5);
	DDRC |=(1<<4);
	DDRC |=(1<<3);
	
	
	
	
	
	
    while(1)
    {	
		
		xTaskCreate(
		task1,   // pointer to function
		"Abdullah",   // descriptive string "doesn't matter"
		100       ,   // stack depth size to be allocated
		NULL ,        // prparms pass parameters to task
		1 ,           // proirity the bigger the more priority
		task1handel          // handler 
		);
		
		
		vTaskStartScheduler();
		
    }
}


void task1(void *ptr)
{
	
	short ss;
	while(1)
	{
		
		
		char input= SPI_SlaveReceive();
		
		if(input == '1')
		{
			PORTC ^= (1<<7);
		}
		if(input == '2')
		{
			PORTC ^= (1<<6);
		}
		if(input == '3')
		{
			PORTC ^= (1<<5);
		}
		if(input == '4')
		{
			PORTC ^= (1<<4);
		}
		if(input == '5')
		{
			input =SPI_SlaveReceive();
			
			if((PORTC & (1<<3)) == 0)
			{
				ss = adc_read(0);
				ss/=2;
				
				if(ss>input+1)
				{
					PORTC |= (1<<3);
				}
			}			
			else
			{
				
				PORTC &=(~(1<<3));
			}
			
		}
		
		
		
		
		
		
		
		
	}
	
}