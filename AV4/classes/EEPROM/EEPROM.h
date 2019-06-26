/*
 * EEPROM.h
 *
 *  Created on: 25 de jun de 2019
 *      Author: paulosell
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include "fila.h"
#include <avr/eeprom.h>

class EEPROM{
public:
	EEPROM(){};
	~EEPROM(){};
	void write(uint8_t * pos, uint8_t byte);
	void write_burst(uint8_t * pos, Fila<uint8_t,10> bytes);
	uint8_t read(uint8_t * pos);


private:

};



#endif /* EEPROM_H_ */
