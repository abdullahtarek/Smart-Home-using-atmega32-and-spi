/*
 * ADC.c
 *
 * Created: 5/11/2018 11:17:08 AM
 *  Author: Abdullah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
char temp;


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
	
	sei();
	
	ADCSRA |= (1<<ADIE);//Enable interrupts
	
}

void ADC_u16convert()
{
	ADCSRA |= (1<<ADSC);
	
	/*while((ADCSRA&(1<<ADIF))==0)
	{
		//wait till converstion completed
	}
	
	ADCSRA |= (1<<ADIF);
	
	unsigned short ret = (ADCL) | (ADCH<<8)  ;
	
	
	return ret;*/
}

