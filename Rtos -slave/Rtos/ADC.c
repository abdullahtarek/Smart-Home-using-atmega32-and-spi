/*
 * ADC.c
 *
 * Created: 5/11/2018 11:17:08 AM
 *  Author: Abdullah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	
	return (ADC);
}



void ADC_vinit()
{
	
	// 5v vref
	ADMUX |=(1<<REFS0);
	ADMUX &= (~(1<<REFS1));
	
	//port number |= (1<<0);
	
	ADCSRA |=(1<<ADEN); // Enable ADC
	
	// devide by 64
	ADCSRA |=(1<<ADPS2);
	ADCSRA |=(1<<ADPS1);
	ADCSRA &= (~(1<<ADPS0));
	
	ADCSRA |= (1<<ADIE);//Enable interrupts
	
}
void ADC_u16convert()
{
	ADCSRA |= (1<<ADSC);
	
	ADCSRA |= (1<<4);
	
	while((ADCSRA&(1<<4))==0)
	{
		//wait till converstion completed
	}
	
	
	unsigned short ret = 0;//(ADCL) | (ADCH<<8)  ;
	
	
	return ret;
}