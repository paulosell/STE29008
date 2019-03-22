/*
 * STEAV1.cpp
 *
 *  Created on: 20 de mar de 2019
 *      Author: paulosell
 */

#include <avr/io.h>
#define FOSC 16000000
#define BAUD 9600
#define myubrr (FOSC/16/BAUD)-1
void setup1(){

	DDRE &= ~(1 << 4); // PORT D2 AS INPUT
	DDRE &= ~(1 << 5); // PORT D3 AS INPUT

	DDRH |= (1 << 5); // PORT D8 AS OUTPUT
	DDRH |= (1 << 6); // PORT D9 AS OUTPUT

}


void setup2(){
	unsigned int ubrr = (FOSC/16/BAUD)-1;

		UBRR0H = (unsigned char) (ubrr >> 8);
		UBRR0L = (unsigned char) ubrr;

		UCSR0B |= (1 << RXEN0);
		UCSR0B |= (1 << TXEN0);

		UCSR0C &= ~(1 << USBS0);
		UCSR0C |= (3 << UCSZ00);

}
void controleBotao5V(){
	// O led conectado no bit 6 da PORTH irá acender
	// Quando o quinto bit da PORT4 estiver em 1
	if (PINE & (1<<5)){
		PORTH |= (1 << 6);

	}
	else {
		PORTH &= ~(1 << 6);
	}

}

void controleBotao0V(){
	// O led conectado no bit 5 da PORTH irá acender
	// Quando o quarto bit da PORT4 estiver em 0
	if (PINE & (1<<4)){
		PORTH &= ~(1 << 5);

	}
	else {
		PORTH |= (1 << 5);
	}

}
void exec1(){

	setup1();
	while(true){
		controleBotao5V();
		controleBotao0V();
	}
}

void exec2(){
	setup2();
	while (true){

			unsigned char byte;
			while ( !(UCSR0A & (1<<RXC0)) )
			;

			byte= UDR0;
			byte = byte + 1;

			while ( !( UCSR0A & (1<<UDRE0)) )
			;
			UDR0 = byte;


}
}


int main(){
	//exec1();
	exec2();

}




