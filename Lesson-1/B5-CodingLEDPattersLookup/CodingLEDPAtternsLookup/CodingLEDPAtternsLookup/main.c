/*
 * CodingLEDPAtternsLookup.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

void displaySequence(short arr[], int arraySize);

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void displaySequence(short arr[], int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		PORTD = arr[i];
		wait(200);
	}
}

int main(void) {
	short toCenterFromCenter[7] = { 0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81 };
	short walkingLeds[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
	
	DDRD = 0xFF;		//B: 0b11111111

	while(1) {
		displaySequence(toCenterFromCenter, 7);
		displaySequence(walkingLeds, 8);
	}
	return 1;
}


