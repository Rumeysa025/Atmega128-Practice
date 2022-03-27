/*
 * CodingStates.c
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
	DDRD = 0xFF;
	int interval = 1000;
	
	while (1) {
		PORTD = 0x80;
		wait(interval);
		PORTD = 0x00;
		wait(interval);
		
		if ((PINC & 0x01) && (interval == 1000)) {
			interval = 250;
			} else if ((PINC & 0x01) && (interval == 250)) {
			interval = 1000;
		}
	}
	
	return 1;
}


