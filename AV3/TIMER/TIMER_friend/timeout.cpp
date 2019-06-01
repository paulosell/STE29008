/*
 * timeout.cpp
 *
 *  Created on: 03/05/2019
 *      Author: aluno
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "timeout.h"

Timeout::Timeout(uint32_t interval, CALLBACK_t callback){
	_interval = interval;
	_counter = 0;
	_pCAllback = callback;
	_enable = false;
	_event = false;
}


void Timeout::enableTimeout(){
	 _enable = true;
}

void Timeout::disableTimeout(){
	 _enable = false;
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


