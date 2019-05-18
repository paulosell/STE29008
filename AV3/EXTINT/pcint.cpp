/*
 * pcint.cpp
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */
#include<avr/interrupt.h>
#include "pcint.h"


PCINT::PCINT(){
	_pCallback = NULL;
	_event = false;
	_enabled = false;
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
	_enabled = true;
}

bool PCINT::isEnabled(){
	return _enabled;
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
	_enabled = false;
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

