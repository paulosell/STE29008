/*
 * uart.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include "uart.h"

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb){
	UBRR0 = getUBRR(baud);
	UCSR0B = 24;
	UCSR0C = db|parity|sb;
}

unsigned int UART::getUBRR(uint32_t baud){
	return ((F_CPU/16/baud)-1);
}

void UART::put(uint8_t data){
	UDR0 = data;
}

uint8_t UART::get(){
	return  UDR0;
}

bool UART::ableToGet(){
	return ((UCSR0A & (1<<RXC0)));
}

bool UART::ableToPut(){
	return ((UCSR0A & (1<<UDRE0)));
}
