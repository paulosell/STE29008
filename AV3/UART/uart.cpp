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
uint8_t UART::_size;
uint8_t UART::quantity_tx;
uint8_t UART::quantity_rx;
uint8_t UART::_rx_buffer[10];
uint8_t UART::_tx_buffer[10];


UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb){
	UBRR0 = getUBRR(baud);
	UCSR0B = 24;
	UCSR0C = db|parity|sb;
	UCSR0B |= (1 << RXCIE0);
	_size = 10;
	quantity_tx = 0;
	quantity_rx = 0;


}

unsigned int UART::getUBRR(uint32_t baud){
	return ((F_CPU/16/baud)-1);
}

void UART::put(uint8_t data){
	if(quantity_tx < _size){
		_tx_buffer[quantity_tx] = data;
		quantity_tx = quantity_tx + 1;

	}
	UCSR0B |= (1 << UDRIE0);
}

uint8_t UART::get(){

	uint8_t data = _rx_buffer[0];
	quantity_rx = quantity_rx - 1;
	if (quantity_rx > 0){
		for(int i = 0; i < quantity_rx - 1; i++){
			_rx_buffer[i] = _rx_buffer[i+1];
			}
	}
	_has_data = (quantity_rx > 0);
	return data;

}

void UART::rxHandler(){
	if(quantity_rx < _size) {
	_rx_buffer[quantity_rx] = UDR0;
	quantity_rx = quantity_rx + 1;
	_has_data = (quantity_rx > 0);
}
}

void UART::txHandler(){
	if(quantity_tx > 0){
	UDR0 = _tx_buffer[0];
	quantity_tx = quantity_tx - 1;
		if (quantity_tx > 1){
			for(int i = 0; i < quantity_tx-1; i++){
				_tx_buffer[i] = _tx_buffer[i+1];
				}
		} else {
			_tx_buffer[0] = _tx_buffer[1];
		}
	}
	if (quantity_tx == 0) {
	UCSR0B &= ~(1 << UDRIE0);
	}
}


bool UART::hasData(){
	return quantity_rx > 0;
}

ISR(USART0_RX_vect){
	UART::rxHandler();
}

ISR(USART0_UDRE_vect){
	UART::txHandler();
}
