/*
 * timeout.cpp
 *
 *  Created on: 03/05/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "timeout.h"

Timeout::Timeout(){}

void Timeout::setTimeout(uint32_t interval, CALLBACK_t callback){
	_interval = interval;
	_counter = 0;
	_pCAllback = callback;
	_enable = true;
	_event = false;
}

bool Timeout::isEnabled(){
	return _enable;
}

bool Timeout::hasEvent(){
	return _event;
}

void Timeout::checkTimeout(){
	if(_counter == _interval){
		_event = true;
		_counter = 0;

	} else {
		_counter = _counter + 1;
		_event = false;
	}

}

void Timeout::disableEvent(){
	_event = false;
}
