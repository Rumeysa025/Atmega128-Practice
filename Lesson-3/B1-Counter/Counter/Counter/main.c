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

void timer2Init(void);

void wait( int ms ) {
	for (int i = 0; i < ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int amountOfTimesPressed;
ISR (TIMER2_COMP_vect) {
	amountOfTimesPressed++;
}

void timer2Init(void) {
	OCR2 = CompareValue;
	TIMSK |= (1 << 7);
	TCCR2 = 0x1F;
	sei();
}

int main(void) {
	DDRA = 0xFF;
	DDRD &= ~(1 << 7);
	lcd_init();
	timer2Init();
	
    /* Replace with your application code */
    while (1) {
		char buffer[10];
		lcd_set_cursor(0x0);
		lcd_display_text(itoa(amountOfTimesPressed, buffer, 10));
		wait(75);
	}
}

