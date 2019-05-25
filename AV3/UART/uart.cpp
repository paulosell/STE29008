/*
 * uart.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"



UART_MAPPER::UART_Mapper * UART::_uartptr;
bool UART::_has_data = false;
Fila<uint8_t, 10> UART::_rx;
Fila<uint8_t, 10> UART::_tx;
uint8_t UART::_id;

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb, DOUBLESPEED_t ds, UARTID_t id){
	_uartptr = UART_MAPPER::AllUarts[id];
	_uartptr->setUART((uint32_t)baud, (uint8_t) parity, (uint8_t) db, (uint8_t) sb, (uint8_t) ds);
	_id = id;
}



void UART::puts(char data[], int len){
	for (int i = 0; i < len; i++){
		put(data[i]);
	}
}

void UART::put(uint8_t data){
	if(!_tx.cheia()){
		_tx.push(data);
		_uartptr->enableInt();
	}
}
uint8_t UART::get(){
	uint8_t data = _rx.pop();
	_has_data = !_rx.vazia();
	return data;

}

void UART::rxHandler(){
	if(!_rx.cheia()){
		_rx.push(_uartptr->getUDR());
		_has_data = true;
	}
}

void UART::txHandler(){
	if(!_tx.vazia()){
		_uartptr->setUDR(_tx.pop());
		if(_tx.vazia()){
		_uartptr->disableInt();
		}
	}
}


bool UART::hasData(){
	return _has_data;
}

ISR(USART0_RX_vect){
	if (UART::_id == 0) UART::rxHandler();
}

ISR(USART0_UDRE_vect){
	if (UART::_id == 0)	UART::txHandler();
}

ISR(USART1_RX_vect){
	if (UART::_id == 1) UART::rxHandler();
}

ISR(USART1_UDRE_vect){
	if (UART::_id == 1)	UART::txHandler();
}

ISR(USART2_RX_vect){
	if (UART::_id == 2) UART::rxHandler();
}

ISR(USART2_UDRE_vect){
	if (UART::_id == 2)	UART::txHandler();
}

ISR(USART3_RX_vect){
	if (UART::_id == 3) UART::rxHandler();
}

ISR(USART3_UDRE_vect){
	if (UART::_id == 3)	UART::txHandler();
}






