/*
 * CodingIO.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void) {
	DDRD = 0xFF;		//B: 0b11111111
	
	while(1) {
		PORTD = 0x80;	//B: 0b10000000;
		wait(500);
		PORTD = 0x40;	//B: 0b01000000;
		wait(500);
	}
	return 1;
}


