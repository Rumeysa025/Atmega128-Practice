/*
 * ADC10Bit.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8e6
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait(int ms) {
	for (int i = 0 ; i < ms ; i++){
		_delay_ms(1);
	}
}

void adcinit( void) {
	ADMUX = 0b11100000;
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRF = 0x00;
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcinit();
	
	while (1) {
		PORTA = ADCH;
		wait(500);
	}
}

