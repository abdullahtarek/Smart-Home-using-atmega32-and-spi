/*
 * SPI.c
 *
 * Created: 9/5/2017 8:35:09 PM
 * 
 */ 

#include "SPI.h"
#include <avr/io.h>


void SPI_MasterInit(void)
{
	/*Set clock to fosc/16*/
	SPCR |= (1<<SPR0);
	SPCR &= (~(1<<SPR1));
	SPCR &= (~(1<<SPI2X));
	
	/*Enable Master mode*/
	SPCR |=(1<<MSTR);
	/*At the End,  Enable SPI*/
	SPCR |=(1<<SPE);
	/*Set SS--> Pin 4 / MOSI --> Pin 5 / SCK --> Pin 7 as outputs for master*/
	DDRB |=(1<<SS);
	DDRB |=(1<<MOSI);
	DDRB |=(1<<SCK);
	
	/*Set SS Pin to high*/
	PORTB |=(1<<SS);
}

void SPI_MasterTransmit(char Data)
{
	/*Clear SS to write to slave*/
	PORTB &=(~(1<<SS));
	/*Put data on bus*/
	SPDR = Data;
	/*Wait until the transmission is finished*/
	while(((SPSR&(1<<SPIF))==0))
	{
		
		
	}
	/*Set SS to high*/
	PORTB |=(1<<SS);
	
}

void SPI_SlaveInit(void)
{
	/*Enable SPI*/
	SPCR |=(1<<SPE);
	/*Set MISO as output*/
	PORTB &=(~(1<<MISO));

}

char SPI_SlaveReceive(void)
{
	/*Wait until data is received in SPI register*/
	while(((SPSR&(1<<SPIF))==0))
	{
		
		
	}
	/*The data arrived read it*/
	
	return SPDR;
}