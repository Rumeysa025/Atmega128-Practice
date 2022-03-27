/*
 * Coding7SegmentDisplayFun.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

typedef struct{
	unsigned char bit;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0b00000001, 100}, {0b00000010, 100}, {0b00000100, 100}, {0b00001000, 100}, //A, B, C, D
	{0b00010000, 100}, {0b01000000, 100}, {0b00000010, 100}, {0b00000001, 100}, //E, G, B, A
	{0b00100000, 100}, {0b01000000, 100}, {0b00000100, 100}, {0b00001000, 100}, //F, G, C, D
	{0b00010000, 100}, {0b01000000, 100}, {0b00000010, 100},					//E, G, B
};

void wait(int ms) {
	for (int i = 0; i < ms; i++) {
		_delay_ms( 1 );        // library function (max 30 ms at 8MHz)
	}
}

int main(void) {
	DDRB = 0xFF;
	int index = 0;
	
	while (1) {
		while(pattern[index].delay != 0) {
			PORTB = pattern[index].bit;
			wait(pattern[index].delay);
			index = (index + 1)%16;
		}
		return 1;
	}
	return 1;
}


