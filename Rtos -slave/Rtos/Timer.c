/*
 * Timer.c
 *
 * Created: 7/12/2018 11:22:06 AM
 *  Author: Abdullah
 */ 
#include <avr/io.h>

void timer_init()
{
	//set timer mode This is CTC mode
	TCCR0 &= (~(1<<WGM00));
	TCCR0 |= 1<<WGM01;
	//choose prescaler this is fcpu/1024
	TCCR0 |= (1<<CS00);
	TCCR0 &= (~(1<<CS01));
	TCCR0 |= (1<<CS02);
	// we want timer to tick every 10ms;; 10ms = ((1024"the prescaler")/(8000000"FCPU"))*OCR0
	OCR0 = 78;
	//enable sie for global interupts
	//ENABLE TIMER INTERRUPTS
	TIMSK |= (1<<OCIE0);
	
}