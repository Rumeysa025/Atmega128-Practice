/*
 * Microcontrollers_Eindproject.c
 *
 * Author : Rümeysa Yavuz en Pascal de Bruijn
 */ 

#define F_CPU 8E6 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define BUZZER_INTERFAL 2273
#define  Trigger_pin PA0	/* Trigger pin */

int TimerOverflow = 0;
long count;
double distance;
int isRising = 1;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}

ISR(INT0_vect)
{
	if(isRising)
	{
		EICRA = 0x02;			//Set interrupt to falling edge
		EIMSK = 0x01;			//Enable INT0
		
		PORTA = 0x00;
		TCNT1 = 0;				//Clear Timer counter
		TCCR1B = 0x02;			//Prescaler = 8
		TimerOverflow = 0;		//Clear timer overflow count
		
		isRising = 0;
	}
	else
	{
		EICRA = 0x03;
		EIMSK = 0x01;
		
		count = TCNT1 + (65535 * TimerOverflow);	// Take count 
		
		distance = (double) count * 0.0343;
		
		PORTA = 0x00;
		TCNT1 = 0;				// Clear Timer counter 
		TCCR1B = 0x02;			// Prescaler = 8 
		TIFR = (1 << ICF1);		// Clear ICP flag (Input Capture flag) 
		TIFR = (1 << TOV1);		// Clear Timer Overflow flag 
		
		isRising = 1;
	}
}

void timer3_init()
{
	ICR3 = BUZZER_INTERFAL; //TOP value for counter
	OCR3A = 0;				//Compare value in between
	TCCR3A = 0x82;			//0b10000010 compare output at OCR3A (=PE3)
	TCCR3B = 0x1A;			//0b00011010 fast PWM, TOP=ICR1, prescaler=8,
}

int main(void)
{
	DDRA = 0xFF;	//Pins[7:0] output		The trigger pin (PA0) needs to be set on output/write.
	DDRB = 0xFF;	//Pins[7:0] output		Used for testing distance with LEDS
	PORTD = 0xFE;	//Pins[7:1] output		Pin[0] input. The echo pin (PD0) needs to be set on input/read.
	DDRE = 0xFF;	//Pins[7:0] output		Set PORTE for compare output

	EICRA = 0x03;	//Pins[7:2] input		Pins[1:0] output	Set interrupt to rising edge
	EIMSK = 0x01;	//Pins[7:1] input		Pin[0] output		Enable INT0
	sei();			//Enable global interrupt
	
	TIMSK = (1 << TOIE1);	//Enable timer1 overflow interrupt
	TCCR1A = 0;				//Set all bit to zero Normal operation
	
	timer3_init();
	wait(100);
	
	while(1)
	{
		PORTA |= (1 << Trigger_pin);	//Trigger_pin = PA0
		_delay_us(10);					//Give 10us trigger pulse on trig.
		PORTA &= (~(1 << Trigger_pin));
		wait(100);
				
		double playingTone = distance; 
		playingTone = playingTone * 47.6;
		playingTone = playingTone + 10;
		playingTone = 1 / playingTone;			//F = 1/t
		playingTone =  playingTone * 1000000;
		
		ICR3 = playingTone;			//TOP value for counter 
		OCR3A = playingTone / 10;	//Compare value in between
		TCCR3A = 0x82;				//0b10000010 compare output at OC3A (=PE3)
		TCCR3B = 0x1A;				//0b00011010 fast PWM, TOP=ICR3, prescaler=8,
	}
    return 1;
}