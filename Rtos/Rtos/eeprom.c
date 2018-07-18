/*
 * eeprom.c
 *
 * Created: 7/11/2018 4:51:09 PM
 *  Author: Abdullah
 */ 
#include <avr/io.h>
void write_eeprom(short address , char data)
{
	while(((EECR& (1<<EEWE))>>EEWE)==1)
	{
		/*wait until EEPROM IS FREE */
	}
	
	//adrress of the EEPROM and because it is 1024 is 12 bits so to chars one high and one low
	EEARL = (char)address;
	EEARH= (char)(address>>8);
	//Set data
	EEDR = data;
	//set master
	EECR |= (1<<EEMWE);
	//set write enable
	EECR |= (1<<EEWE);
}
char read_eeprom(short address)
{
	while( ((EECR & (1<<EEWE))>>EEWE) ==1)
	{
		//wiat until EEPROM is free	
	}
	
	//adress
	EEARL = (char)address;
	EEARH= (char)(address>>8);
	//
	EECR |= (1<<EERE);
	
	return EEDR;	
}