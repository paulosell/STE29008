/*
 * main.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "EEPROM.h"
int main(){
	sei();
	UART uart0((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART0);
	EEPROM e;
	uint8_t * pos = 0;
	uint8_t dado = 0x30;
	e.write(pos, dado);
	eeprom_write_byte(pos+1, dado+1);
	Fila<uint8_t,10> fila;
	for(int i =0; i < 10; i++){
		fila.push((uint8_t) (i+0x30));
	}

	e.write_burst(pos, fila);
	while(true){
		uint8_t * _pos= 0;
		for (uint8_t  i = 0; i < 10; i++){
			uart0.put(e.read(_pos));
			_pos++;
		}

		_delay_ms(1000);
	}



}
