/*
 * pcint.cpp
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */
#include <avr/io.h>
#include "pcint.h"
#include "GPIO.h"

PCINT::PCINT(){
	_pCallback = NULL;
	_event = false;
}

void PCINT::enable(PCINT_ID_t id){
	if (id < 8){
		PCMSK0 |= (1 << id);
	}
	else if (id >=8 and id < 16){
		PCMSK1 |= (1 << (id - 8));
	}
	else if (id >= 16 and id < 24){
		PCMSK2 |= (1 << (id - 16));
	}
}

void PCINT::disable(PCINT_ID_t id){
	if (id < 8){
		PCMSK0 &= ~(1 << id);
	}
	else if (id >=8 and id < 16){
		PCMSK1 &= ~(1 << (id - 8));
	}
	else if (id >= 16 and id < 24){
		PCMSK2 &= ~(1 << (id - 16));
	}
}

void PCINT::setCallback(CALLBACK_t callback){
	_pCallback = callback;
}
void PCINT::setEvent(bool event){
	_event = event;
}

bool PCINT::event(){
	return _event;
}

