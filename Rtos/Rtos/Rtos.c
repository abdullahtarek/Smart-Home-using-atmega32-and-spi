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

int x =0;
int y=0;

TaskHandle_t led1handel = NULL;
TaskHandle_t loginsreenhandel = NULL;
TaskHandle_t checkpassowrdhandel =NULL;
TaskHandle_t adminpagehandel =NULL;
TaskHandle_t blockhandel =NULL;
TaskHandle_t guestpagehandel =NULL;

char loginstat=0;
char passin[4];
double timecount=0;
char flagdisconect = 0;


void checkpassowrd(void *ptr);
void adminpage(void *ptr);
void loginsreen(void *ptr);
void block(void *ptr);
void guestpage(void *ptr);





int main(void)
{
	sei();
	LCD_VINIT();
	keypad_init();
	timer_init();
	SPI_MasterInit();
	
	DDRD |=(1<<7);
	DDRD |=(1<<6);
	DDRD |=(1<<5);
	DDRD |=(1<<4);
	
	
	
    while(1)
    {	
		if(read_eeprom(5)!='1')
		{
			xTaskCreate(
			loginsreen,   // pointer to function
			"Abdullah",   // descriptive string "doesn't matter"
			50       ,   // stack depth size to be allocated
			NULL ,        // prparms pass parameters to task
			1 ,           // proirity the bigger the more priority
			loginsreenhandel          // handler 
			);
		}
		else
		{
			xTaskCreate(block,"Abdullah",50,NULL ,1 ,blockhandel);
		}	
		
		
		vTaskStartScheduler();
		
    }
}


void block(void *ptr)
{
	PORTD &= (~(1<<7));
	PORTD &= (~(1<<6));
	PORTD &= (~(1<<5));
	PORTD &= (~(1<<4));
	PORTD |= (1<<4);
	
	clear_screen();
	LCD_VsnedString("blocked");
	write_eeprom(5,'1');
	loginstat=3;
	while(1)
	{
		if(flagdisconect ==1)
		{
			xTaskCreate(loginsreen,"checkpass",50,NULL,1,loginsreenhandel);
			vTaskDelete(blockhandel);
			
			
			write_eeprom(5,'0');
			
		}
		else
		{
			PORTD ^=(1<<3);
			_delay_ms(1000);
			
		}
		
		
	}
}
void adminpage(void *ptr)
{
	loginstat =1;
	PORTD &= (~(1<<7));
	PORTD &= (~(1<<6));
	PORTD &= (~(1<<5));
	PORTD &= (~(1<<4));
	PORTD |= (1<<6);
	
	clear_screen();
	writeadminscreen();
	char input;
	
	char temp[2];
	
	int ftemp=0;
	
	while(1)
	{
		
		//code for sending the instructions here
		
		input= check();
		
		if(input != 0 )
		{
			_delay_ms(300);
			
			if(ftemp >0)
			{
				LCD_vsendData(input);
				temp[2-ftemp]=input;
				
				if(ftemp == 1)
				{
					
					clear_screen();
					LCD_VGOTO(0,0);
					writeadminscreen();
					temp[0] = temp[0] - '0';
					temp[1]-= '0';
					
					char tt = (temp[0]*10)+temp[1];
					
					SPI_MasterTransmit(tt);
				}
				
				
				ftemp --;
			}
			else
			{
				if(input=='1' || input=='2' || input=='3' || input=='4'||input=='5')
				{
					SPI_MasterTransmit(input);
					if(input=='5')
					{
						ftemp =2;
						clear_screen();
						LCD_VsnedString("Temp");
						LCD_VGOTO(1,0);
					}
				}
			}			
			
			
			
		}			
		
		
		
		if(flagdisconect == 1)
		{
			
			PORTD |=(1<<4);
			
			xTaskCreate(loginsreen,"checkpass",50,NULL,1,loginsreenhandel);
			vTaskDelete(adminpagehandel);
		}
		else
		{
			PORTD ^=(1<<3);
			_delay_ms(200);
		}
		
	}
	
	
}
void checkpassowrd(void *ptr)
{
	char col=0;
	clear_screen();
	char wrongpasswordcount=0;

	
	char pass_exists = read_eeprom(0);
	
	if(pass_exists !='0')
	{
		writeSetpassword();
	}
	else
	{
		LCD_VsnedString("Password:");
	}
	
	LCD_VGOTO(1,col);
	PORTD |= (1<<7);
	
	char input;
	char index= 0;
	while(1)
	{
		input= check();
		
		if(input != 0 )
		{
			_delay_ms(300);
			LCD_vsendData(input);
			_delay_ms(200);
			LCD_VGOTO(1,col);
			LCD_vsendData('*');
			passin[col] = input;
			
			if(col == 3)
			{
				if(pass_exists !='0')
				{
					write_eeprom(0 , '0');
					write_eeprom(1 , passin[0]);
					write_eeprom(2 , passin[1]);
					write_eeprom(3 , passin[2]);
					write_eeprom(4 , passin[3]);
					
					
					xTaskCreate(adminpage,"checkpass",100,NULL,1,adminpagehandel);
					vTaskDelete(checkpassowrdhandel);
					
				}
				else
				{
					char pass[4];
					pass[0]= read_eeprom(1);
					pass[1]= read_eeprom(2);
					pass[2]= read_eeprom(3);
					pass[3]= read_eeprom(4);
					
					if(passin[0]==pass[0]&&passin[1]==pass[1]&& passin[2]==pass[2]&&passin[3]==pass[3])
					{
						xTaskCreate(adminpage,"checkpass",100,NULL,1,adminpagehandel);
						vTaskDelete(checkpassowrdhandel);
					}
					else
					{
						clear_screen();
						writewrongpassword();
						_delay_ms(1000);
						clear_screen();
						LCD_VsnedString("Password:");
						LCD_VGOTO(1,0);
						col=-1;
						wrongpasswordcount++;
						if(wrongpasswordcount ==3)
						{
							xTaskCreate(block,"checkpass",100,NULL,1,loginsreenhandel);
							vTaskDelete(checkpassowrdhandel);
							
						}
						
					}
					
					
					

				}
				
			}
			
			
			col++;
		}
		
		
		
	}
}
void loginsreen(void *ptr)
{
	write_eeprom(5,'0');	
	char input;
	clear_screen();
	loginstat =0;
	timecount=0;
	flagdisconect =0;
	
	PORTD &= (~(1<<7));
	PORTD &= (~(1<<6));
	PORTD &= (~(1<<5));
	PORTD &= (~(1<<4));
	PORTD |= (1<<7);
	writeloginscreen();
	
	while(1)
	{
		input= check();
		
		if(input != 0 )
		{
			_delay_ms(300);
			if(input == '1')
			{
				xTaskCreate(checkpassowrd,"checkpass",100,NULL,1,checkpassowrdhandel);
				vTaskDelete(loginsreenhandel);
			}
			if(input == '2')
			{
				xTaskCreate(guestpage,"checkpass",100,NULL,1,guestpagehandel);
				vTaskDelete(loginsreenhandel);
			}
			
		}
		
	}
	
}
void guestpage(void *ptr)
{
	PORTD &= (~(1<<7));
	PORTD &= (~(1<<6));
	PORTD &= (~(1<<5));
	PORTD &= (~(1<<4));
	
	PORTD |= (1<<5);
	
	loginstat =2;
	clear_screen();
	writeguestscreen();
	char input;
	
	while(1)
	{
		
		input= check();
		
		if(input != 0 )
		{
			_delay_ms(300);
			if(input=='1' || input=='2' || input=='3')
			{
				SPI_MasterTransmit(input);
			}
		}
		
		
		if(flagdisconect == 1)
		{
			
			xTaskCreate(loginsreen,"checkpass",50,NULL,1,loginsreenhandel);
			vTaskDelete(guestpagehandel);
		}
		else
		{
			PORTD ^=(1<<3);
			_delay_ms(200);
		}
		
	}
}





ISR(TIMER0_COMP_vect)
{
	if(loginstat !=0)
	{
		
		if(loginstat==1 && timecount ==60000)
		{
			flagdisconect = 1;
		}
		if(loginstat==2 && timecount ==30000)
		{
			flagdisconect = 1;
		}
		
		if(loginstat==3 && timecount ==90000)
		{
			flagdisconect=1;
		}
		
		
		timecount++;
		
	}
	
	
	
	
	
}