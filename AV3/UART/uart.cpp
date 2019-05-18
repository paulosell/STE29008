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
Fila<uint8_t, 10> UART::_rx;
Fila<uint8_t, 10> UART::_tx;


UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb, DOUBLESPEED_t ds){
	UBRR0 = getUBRR(baud, ds);
	UCSR0B = 24;
	UCSR0C = db|parity|sb;
	UCSR0B |= (1 << RXCIE0);
	if(ds == 0){
		UCSR0A &= ~(1 << U2X0);
	} else {
		UCSR0A |= (1 << U2X0);
	}
}

unsigned int UART::getUBRR(uint32_t baud, DOUBLESPEED_t ds){
	if (ds == 0){
		return ((F_CPU/16/baud)-1);
	} else {
		return ((F_CPU/8/baud)-1);
	}
}

void UART::puts(char data[], int len){
	for (int i = 0; i < len; i++){
		put(data[i]);
	}
}

void UART::put(uint8_t data){
	if(!_tx.cheia()){
		_tx.push(data);
		UCSR0B |= (1 << UDRIE0);
	}
}
uint8_t UART::get(){
	uint8_t data = _rx.pop();
	_has_data = !_rx.vazia();
	return data;

}

void UART::rxHandler(){
	if(!_rx.cheia()){
		_rx.push(UDR0);
		_has_data = true;
	}
}

void UART::txHandler(){
	if(!_tx.vazia()){
		UDR0 = _tx.pop();
		if(_tx.vazia()){
		UCSR0B &= ~(1<<UDRIE0);
		}
	}
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



