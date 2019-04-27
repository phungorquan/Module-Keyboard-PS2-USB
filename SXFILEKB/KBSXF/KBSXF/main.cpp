/*
 * KBSXF.cpp
 *
 * Created: 2/16/19 10:46:44 PM
 * Author : Xiu
 */ 

#include "KBSXF.h"

PS2Keyboard keyboard;

int main() {
	keyboard.begin();
	
	//Setup for USB KEYBOARD
	cbi(DDRB,0);
	cbi(DDRB,1);

	sbi(PORTB,0);	
	sbi(PORTB,1);
	
	//Setup INT
	GIMSK |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	sei();
	
	
	// Setup Timer for UART
	TCCR0A = 0x02;  // CTC
	TCCR0B = 0x02;  // prescaller 8
	OCR0A  = uart_delay;  // ... delay
	uart_init(); // init ;)
	


	while(1)
	{
		
		//bit_bang_tx('X');
		//_delay_ms(100);
		
		if(keyboard.available()) {
			uint8_t dat = keyboard.read();
			bit_bang_tx(dat);
		}
	}

	return 0;
}

