/*
 * CodingLEDPatterns.c
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
	int i = 0;
	
	while(1) {
		PORTD = 1 << i % 8;
		i++;
		wait(50);
	}
	return 1;
}


