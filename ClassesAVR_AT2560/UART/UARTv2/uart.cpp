/*
 * uart.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

bool UART::_has_data = false;
uint8_t UART::_rx_buffer = 0;
uint8_t UART::_tx_buffer = 0;


UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb){
	UBRR0 = getUBRR(baud);
	UCSR0B = 24;
	UCSR0C = db|parity|sb;
	UCSR0B |= (1 << RXCIE0);

}

unsigned int UART::getUBRR(uint32_t baud){
	return ((F_CPU/16/baud)-1);
}

void UART::put(uint8_t data){
	_tx_buffer = data;
	UCSR0B |= (1 << UDRIE0);
}

uint8_t UART::get(){
	_has_data = false;
	return _rx_buffer;
}

void UART::rxHandler(){
	_rx_buffer = UDR0;
	_has_data = true;
}

void UART::txHandler(){
	UDR0 = _tx_buffer;
	UCSR0B &= ~(1 << UDRIE0);
}

bool UART::hasData(){
	return _has_data;
}

ISR(USART0_RX_vect){
	UART::rxHandler();
}

ISR(USART0_UDRE_vect){
	UART::txHandler();
}
