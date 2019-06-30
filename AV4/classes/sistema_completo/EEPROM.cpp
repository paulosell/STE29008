/*
 * EEPROM.cpp
 *
 *  Created on: 25 de jun de 2019
 *      Author: paulosell
 */

#include "EEPROM.h"

void EEPROM::write(uint8_t * pos, uint8_t byte){
	eeprom_write_byte(pos, byte);
}

void EEPROM::write_burst(uint8_t * pos, Fila<uint8_t,10> bytes){
	uint8_t * _pos = pos;
	while(!bytes.vazia()){
		eeprom_write_byte(_pos, bytes.pop());
		_pos++;

	}
}

uint8_t EEPROM::read(uint8_t * pos){
	return eeprom_read_byte(pos);
}

Fila<uint8_t, 10> read_burst(uint8_t * pos, uint8_t num_bytes){
	Fila<uint8_t, 10> fila;
	uint8_t * _pos = pos;

	for(int i = 0; i < num_bytes; i++){
		fila.push(eeprom_read_byte(_pos));
		_pos++;
	}
	return fila;
}

