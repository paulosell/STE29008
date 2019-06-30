/*
 * uart.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"



//UART_MAPPER::UART_Mapper * UART::_uartptr;
//bool UART::_has_data = false;

UART * UART:: uarts_singletons[4];
//uint8_t UART::_id;

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb, DOUBLESPEED_t ds, UARTID_t id){
	_uartptr = UART_MAPPER::AllUarts[id];
	_uartptr->setUART((uint32_t)baud, (uint8_t) parity, (uint8_t) db, (uint8_t) sb, (uint8_t) ds);
	_id = id;
	_has_data = false;
	uarts_singletons[id] = this;
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

void UART::rxHandler(uint8_t id){
	if(!uarts_singletons[id]->_rx.cheia()){
		uarts_singletons[id]->_rx.push(uarts_singletons[id]->_uartptr->getUDR());
		uarts_singletons[id]->_has_data = true;
	}
}

void UART::txHandler(uint8_t id){
	if(!uarts_singletons[id]->_tx.vazia()){
		uarts_singletons[id]->_uartptr->setUDR(uarts_singletons[id]->_tx.pop());
		if(uarts_singletons[id]->_tx.vazia()){
			uarts_singletons[id]->_uartptr->disableInt();
		}
	}
}


bool UART::hasData(){
	return _has_data;
}

ISR(USART0_RX_vect){
	UART::rxHandler(0);
}

ISR(USART0_UDRE_vect){
	UART::txHandler(0);
}

ISR(USART1_RX_vect){
	UART::rxHandler(1);
}

ISR(USART1_UDRE_vect){
	UART::txHandler(1);
}

ISR(USART2_RX_vect){
	 UART::rxHandler(2);
}

ISR(USART2_UDRE_vect){
	UART::txHandler(2);
}

ISR(USART3_RX_vect){
	UART::rxHandler(3);
}

ISR(USART3_UDRE_vect){
	UART::txHandler(3);
}






