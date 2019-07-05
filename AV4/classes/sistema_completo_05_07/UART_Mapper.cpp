/*
 * UART_Mapper.cpp
 *
 *  Created on: 25 de mai de 2019
 *      Author: paulosell
 */

#include "UART_Mapper.h"
#include <avr/io.h>
namespace UART_MAPPER{

enum UART_ADDR_BASE{
	UART0 = 0x00C0,
	UART1 = 0x00C8,
	UART2 = 0x00D0,
	UART3 = 0x0130
};

UART_Mapper * AllUarts[4]={
		reinterpret_cast<UART_Mapper*>(UART0),
		reinterpret_cast<UART_Mapper*>(UART1),
		reinterpret_cast<UART_Mapper*>(UART2),
		reinterpret_cast<UART_Mapper*>(UART3)

};


void UART_Mapper::setUART(uint32_t baud, uint8_t parity, uint8_t db, uint8_t sb, uint8_t ds){
	if (ds == 0){
		UBRRH =  (((F_CPU/16/baud)-1)>>8);
		UBRRL =  ((F_CPU/16/baud)-1);
	} else {
		UBRRH =  (((F_CPU/8/baud)-1)>>8);
		UBRRL =  ((F_CPU/8/baud)-1);
	}

	UCSRB = 24;
	UCSRC = db|parity|sb;
	UCSRB |= (1 << 7);

	if(ds == 0){
		UCSRA &= ~(1 << 1);
	} else {
		UCSRA |= (1 << 1);
	}
}

uint8_t UART_Mapper::getUDR(){
	return UDR;
}

void UART_Mapper::setUDR(uint8_t data){
	UDR = data;
}

void UART_Mapper::enableInt(){
	UCSRB |= (1 << 5);
}

void UART_Mapper::disableInt(){
	UCSRB &= ~(1<<5);
}
}


