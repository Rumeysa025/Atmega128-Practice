/*
 * IOSmartControlTri-State.c
 *
 * Author : Rümeysa Yavuz
 */ 

#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>

void setCharliePlexingLed(int lednr);

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void setCharliePlexingLed(int lednr) {
	
	switch(lednr) {
		case 0:		//LED1
		DDRD = 0xFB;	//0b11111011
		PORTD = 0x01;	//0b00000001
		break;
		
		case 1:		//LED2
		DDRD = 0xFB;	//0b11111011
		PORTD = 0x02;	//0b00000010
		break;
		
		case 2:		//LED3
		DDRD = 0xFE;	//0b11111110
		PORTD = 0x02;	//0b00000010
		break;
		
		case 3:		//LED4
		DDRD = 0xFE;	//0b11111110
		PORTD = 0x04;	//0b00000100
		break;
		
		case 4:		//LED5
		DDRD = 0xFD;	//0b11111101
		PORTD = 0x01;	//0b00000001
		break;
		
		case 5:		//LED6
		DDRD = 0xFD;	//0b11111101
		PORTD = 0x04;	//0b00000100
		break;
	}
}

int main(void) {
	DDRD = 0xFF;
	int count = 5;
	
	while (1) {
		for (int i = 0; i <= count; i++) {
			setCharliePlexingLed(i);
			wait(500);
		}
	}
	
	return 1;
}


