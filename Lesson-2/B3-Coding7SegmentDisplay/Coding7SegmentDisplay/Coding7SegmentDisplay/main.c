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
	0b00111111, //1
	0b00000101, //2
	0b01011011, //3
	0b01001111, //4
	0b01100101, //5
	0b01111110, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01101111, //A
	0b01111100, //B
	0b00111010, //C
	0b01011101, //d
	0b01111010, //E
	0b01110010, //F
};

int number = 0;

ISR(INT0_vect) {
	number++;
	if (PIND & 0x02) {
		number = 0;
	}
}

ISR(INT1_vect) {
	number--;
	if(PIND & 0x01) {
		number = 0;
	}
}

int main(void) {
	DDRB = 0xFF; //Pins PORTB output
	DDRD = 0x00; //Pins PORTD input
	EICRA |= 0x0F; //pins 0-1 rising edge
	EIMSK |= 0x03; //enable pin 0-1
	
	sei();
	
	PORTB = NUMBERS[0];
	
	while (1) {
		if (number >= 0 && number <= 15) {
			PORTB = NUMBERS[number];
		}
		else {
			PORTB = NUMBERS[14];
		}
		wait(10);
	}
}

