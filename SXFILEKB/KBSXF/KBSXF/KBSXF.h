/*
 * KBSXF.h
 *
 * Created: 2/16/19 10:47:19 PM
 *  Author: Xiu
 */ 


#define F_CPU 1200000UL 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#define sbi(PORT,bit) {PORT |=(1<<bit);}
#define cbi(PORT,bit) {PORT &=~(1<<bit);}


#define UART_PIN_BIT 2  //to RxD
#define uart_PIN	PB2 //to RxD // 2-Doneboard , 4-LoadCodeBoard
#define uart_delay	14  //  31 = 4800pu ,14 = 9600 ssu,pu , 27 4800 ssu 
#define uart_DDR    DDRB
#define uart_PORT   PORTB	


#define PS2_KC_BREAK  0xf0 // Check Break

class PS2Keyboard {
  public:
	
   	PS2Keyboard();
     
    void begin();		

    bool available();
    
    uint8_t read();
    
};

void begin();
bool available();
uint8_t read();
void bit_bang_tx(uint8_t);
void uart_init();