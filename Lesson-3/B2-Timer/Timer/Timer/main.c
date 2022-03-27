/*
 * Counter.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "lcd.h"

#define CompareValue 1;

void initTimer(void);
void timer2Init(void);

void wait( int ms ) {
	for (int i = 0; i < ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int msCount = 0;
char isOn = 0;
ISR (TIMER2_COMP_vect) {
	msCount++; // Increment ms counter
	if ( msCount == 25 && isOn == 0) {
		isOn = 1;
		PORTD ^= (1 << 7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	} else if(msCount == 15 && isOn == 1) {
		isOn = 0;
		PORTD ^= (1 << 7); // Toggle bit 7 van PORTD
		msCount = 0; // Reset ms_count value
	}
}

void initTimer( void ) {
	OCR2 = 250;
	TIMSK|= (1 << 7);
	TCCR2 = 0x07;
	DDRC = 0xff;
}

void timer2Init(void) {
	OCR2 = 125;				// Compare value of counter 2
	TIMSK |= (1 << 7);		// T2 compare match interrupt enable
	TCCR2 = 0b00001011;
}

int main(void) {
    lcd_init();
    timer2Init();
    sei();
    DDRD = 0xff;
	
    while (1) {
		wait(100);
	}
}

