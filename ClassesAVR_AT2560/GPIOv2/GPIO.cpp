/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */

#include "GPIO.h"

GPIO::GPIO(int pin, PortDirection_t dir)
{
	switch(pin){
	case 2:
		_pin = PE4;
		_port = GPIO_PORT::PE;
		break;
	case 3:
		_pin = PE5;
		_port = GPIO_PORT::PE;
		break;
	case 4:
		_pin = PG5;
		_port = GPIO_PORT::PG;
		break;
	case 5:
		_pin = PE3;
		_port = GPIO_PORT::PE;
		break;
	case 6:
		_pin = PH3;
		_port = GPIO_PORT::PH;
		break;
	case 7:
		_pin = PH4;
		_port = GPIO_PORT::PH;
		break;
	case 8:
		_pin = PH5;
		_port = GPIO_PORT::PH;
		break;
	case 9:
		_pin = PH6;
		_port = GPIO_PORT::PH;
		break;
	}

	_port->dir(_pin, dir);
}

GPIO::~GPIO() {}

bool GPIO::get() {
	return _port->get(_pin);
}

void GPIO::set(bool val) {
	_port->set(_pin, val);
}

void GPIO::clear() {
	this->set(0);
}

void GPIO::toggle() {
	_port->toggle(_pin);
}
