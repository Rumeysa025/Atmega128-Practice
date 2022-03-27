/*
 * Coding7SegmentDisplay.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char NUMBERS[16] = {
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b01111100, //B
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
	0b01110001, //F
};

int number = 0;

ISR(INT0_vect) {
	number++;
}

ISR(INT1_vect) {
	number--;
}

ISR(INT2_vect) {
	number = 0;
}

int main(void) {
	DDRB = 0xFF; //Pins PORTB output
	DDRD = 0x00; //Pins PORTD input
	EICRA |= 0x3F; 
	EIMSK |= 0x07; 
	
	sei();
	
	PORTB = NUMBERS[0];
	
	while (1) {
		if (number >= 0 && number <= 15) {
			PORTB = NUMBERS[number];
		}
		else {
			PORTB = NUMBERS[14];
		}
		wait(100);
	}
}

