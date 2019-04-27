/*
 * KBSXF.cpp
 *
 * Created: 2/16/19 10:47:29 PM
 *  Author: Xiu
 */ 

#include "KBSXF.h"

uint8_t ps2Keyboard_CurrentBuffer;
volatile uint8_t ps2Keyboard_CharBuffer;
uint8_t ps2Keyboard_BufferPos;
bool ps2Keyboard_BreakActive;
int value;


// The ISR for the external interrupt
ISR(INT0_vect) {
	//int value = digitalRead(ps2Keyboard_DataPin);
	
	if((PINB & 0x01)==0)	// Code if thay cho dong tren trong arduino
	{
		value = 0;
	}
	else value = 1;
	
	
	if(ps2Keyboard_BufferPos > 0 && ps2Keyboard_BufferPos < 9) {
		ps2Keyboard_CurrentBuffer |= (value << (ps2Keyboard_BufferPos - 1));
	}
	
	ps2Keyboard_BufferPos++;
	
	if(ps2Keyboard_BufferPos == 11) {	// Loai bo them 2 ky tu break
		if(ps2Keyboard_CurrentBuffer == PS2_KC_BREAK) {
			ps2Keyboard_BreakActive = true;
			} else if(ps2Keyboard_BreakActive) {
			ps2Keyboard_BreakActive = false;
			} else {
			ps2Keyboard_CharBuffer = ps2Keyboard_CurrentBuffer;
			
		}

		ps2Keyboard_CurrentBuffer = 0;
		ps2Keyboard_BufferPos = 0;
	}

}

PS2Keyboard::PS2Keyboard() {
	// nothing to do here
}

void PS2Keyboard::begin() {
	// Prepare the global variables
	ps2Keyboard_CurrentBuffer = 0;
	ps2Keyboard_CharBuffer = 0;
	ps2Keyboard_BufferPos = 0;
	ps2Keyboard_BreakActive = false;

}

bool PS2Keyboard::available() {
	return ps2Keyboard_CharBuffer != 0;
}

uint8_t PS2Keyboard::read() {
	uint8_t result = ps2Keyboard_CharBuffer;

	ps2Keyboard_CharBuffer = 0;
	
	return result;
}

void bit_bang_tx(uint8_t data) {
	int i;
	cbi(PORTB,UART_PIN_BIT);   // start bit
	TCNT0 = 0;						// timer to 0
	while (TCNT0 < uart_delay); // delay
	//------ 1 or 0 to serial port-----------
	for (i = 0; i < 8; i++) {
		if (data & (0x01 << i)) uart_PORT |= (1<<uart_PIN);
		else cbi(PORTB,UART_PIN_BIT);
		//---------------------------------------
		while (TCNT0 < uart_delay); // delay
	}
	sbi(PORTB,UART_PIN_BIT);       // stop bit
	while (TCNT0 < uart_delay);  // delay
}

void uart_init() {
	sbi(DDRB,UART_PIN_BIT);
	sbi(PORTB,UART_PIN_BIT);
	
}