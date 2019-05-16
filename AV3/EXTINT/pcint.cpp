/*
 * pcint.cpp
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */
#include <avr/io.h>
#include "pcint.h"
#include "GPIO.h"
PCINT * PCINT::_PCINT_vect[24];

PCINT::PCINT(PCINT_ID_t id, CALLBACK_t callback){
	_id = id;
	_pCallback = callback;

	if (id < 8){
		PCICR |= (1 << 0);
	}
	else if (id >=8  and id < 16){
		PCICR |= (1 << 1);
	}
	else if (id >= 16 and id < 24){
		PCICR |= (1 << 2);
	}

	_event = false;
	disable(id);
	_PCINT_vect[id] = this;
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

void PCINT::setEvent(bool event){
	_event = event;
}

bool PCINT::event(){
	return _event;
}

void PCINT::checkEvents(){
	for (int i = 0; i < 24; i++){
		if (_PCINT_vect[i]->event()){
			_PCINT_vect[i]->callback();
			_PCINT_vect[i]->setEvent(false);
		}
	}
}
ISR(PCINT0_vect)
{
	if (PINB & (1 << 0)){
		PCINT::_PCINT_vect[0]->setEvent(true);
	}
	else if (PINB & (1 << 1)){
		PCINT::_PCINT_vect[1]->setEvent(true);
	}
	else if (PINB & (1 << 2)){
		PCINT::_PCINT_vect[2]->setEvent(true);;
	}

	else if (PINB & (1 << 3)){
		PCINT::_PCINT_vect[3]->setEvent(true);
	}

	else if (PINB & (1 << 4)){
		PCINT::_PCINT_vect[4]->setEvent(true);
	}

	else if (PINB & (1 << 5)){
		PCINT::_PCINT_vect[5]->setEvent(true);
	}

	else if (PINB & (1 << 6)){
		PCINT::_PCINT_vect[6]->setEvent(true);
	}

	else if (PINB & (1 << 7)){
		PCINT::_PCINT_vect[7]->setEvent(true);
	}

}

ISR(PCINT1_vect)
{
	if (PINE & (1 << 0)){
		PCINT::_PCINT_vect[8]->setEvent(true);
	}
	else if (PINJ & (1 << 0)){
		PCINT::_PCINT_vect[9]->setEvent(true);
	}
	else if (PINJ & (1 << 1)){
		PCINT::_PCINT_vect[10]->setEvent(true);
	}

	else if (PINJ & (1 << 2)){
		PCINT::_PCINT_vect[11]->setEvent(true);
	}

	else if (PINJ & (1 << 3)){
		PCINT::_PCINT_vect[12]->setEvent(true);
	}

	else if (PINJ & (1 << 4)){
		PCINT::_PCINT_vect[13]->setEvent(true);
	}

	else if (PINJ & (1 << 5)){
		PCINT::_PCINT_vect[14]->setEvent(true);
	}

	else if (PINJ & (1 << 6)){
		PCINT::_PCINT_vect[15]->setEvent(true);
	}

}


ISR(PCINT2_vect)
{
	if (PINK & (1 << 0)){
		PCINT::_PCINT_vect[16]->setEvent(true);
	}
	else if (PINK & (1 << 1)){
		PCINT::_PCINT_vect[17]->setEvent(true);
	}
	else if (PINK & (1 << 2)){
		PCINT::_PCINT_vect[18]->setEvent(true);
	}

	else if (PINK & (1 << 3)){
		PCINT::_PCINT_vect[19]->setEvent(true);
	}

	else if (PINK & (1 << 4)){
		PCINT::_PCINT_vect[20]->setEvent(true);
	}

	else if (PINK & (1 << 5)){
		PCINT::_PCINT_vect[21]->setEvent(true);
	}

	else if (PINK & (1 << 6)){
		PCINT::_PCINT_vect[22]->setEvent(true);
	}

	else if (PINK & (1 << 7)){
		PCINT::_PCINT_vect[23]->setEvent(true);
	}

}
