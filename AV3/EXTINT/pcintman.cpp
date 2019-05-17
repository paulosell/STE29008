/*
 * pcintman.cpp
 *
 *  Created on: 17 de mai de 2019
 *      Author: aluno
 */



#include <stdio.h>
#include "GPIO.h"
#include <avr/interrupt.h>
#include "pcint.h"
#include "pcintman.h"
#include <avr/io.h>
#include <util/delay.h>

PCINT PCINTMANAGER::_PCINT_vect[24];


PCINTMANAGER::PCINTMANAGER(){
	PCICR = 1<<PCIE0;
	PCICR = 1<<PCIE1;
	PCICR = 1<<PCIE2;
	for (int i = 0; i < 24; i++){
		PCINT p;
		_PCINT_vect[i] = p;
		_PCINT_vect[i].setEvent(false);

	}
}

void PCINTMANAGER::addPCINT(PCINT::PCINT_ID_t id, CALLBACK_t callback){
	_PCINT_vect[id].setCallback(callback);
	_PCINT_vect[id].enable(id);
}

void PCINTMANAGER::disable(PCINT::PCINT_ID_t id){
	_PCINT_vect[id].disable(id);
}


void PCINTMANAGER::enable(PCINT::PCINT_ID_t id){
	_PCINT_vect[id].enable(id);
}

void PCINTMANAGER::checkEvents(){
	for (int i = 0; i < 24; i++){
		if (_PCINT_vect[i].event()){
			_PCINT_vect[i].callback();
			_PCINT_vect[i].setEvent(false);
		}
	}
}

ISR(PCINT0_vect)
{
	if (PINB & (1 << 0)){
		PCINTMANAGER::_PCINT_vect[0].setEvent(true);
	}
	else if (PINB & (1 << 1)){
		PCINTMANAGER::_PCINT_vect[1].setEvent(true);
	}
	else if (PINB & (1 << 2)){
		PCINTMANAGER::_PCINT_vect[2].setEvent(true);;
	}

	else if (PINB & (1 << 3)){
		PCINTMANAGER::_PCINT_vect[3].setEvent(true);
	}

	else if (PINB & (1 << 4)){
		PCINTMANAGER::_PCINT_vect[4].setEvent(true);
	}

	else if (PINB & (1 << 5)){
		PCINTMANAGER::_PCINT_vect[5].setEvent(true);
	}

	else if (PINB & (1 << 6)){
		PCINTMANAGER::_PCINT_vect[6].setEvent(true);
	}

	else if (PINB & (1 << 7)){
		PCINTMANAGER::_PCINT_vect[7].setEvent(true);
	}

}

ISR(PCINT1_vect)
{
	if (PINE & (1 << 0)){
		PCINTMANAGER::_PCINT_vect[8].setEvent(true);
	}
	else if (PINJ & (1 << 0)){
		PCINTMANAGER::_PCINT_vect[9].setEvent(true);
	}
	else if (PINJ & (1 << 1)){
		PCINTMANAGER::_PCINT_vect[10].setEvent(true);
	}

	else if (PINJ & (1 << 2)){
		PCINTMANAGER::_PCINT_vect[11].setEvent(true);
	}

	else if (PINJ & (1 << 3)){
		PCINTMANAGER::_PCINT_vect[12].setEvent(true);
	}

	else if (PINJ & (1 << 4)){
		PCINTMANAGER::_PCINT_vect[13].setEvent(true);
	}

	else if (PINJ & (1 << 5)){
		PCINTMANAGER::_PCINT_vect[14].setEvent(true);
	}

	else if (PINJ & (1 << 6)){
		PCINTMANAGER::_PCINT_vect[15].setEvent(true);
	}
	//_delay_ms(200);
}


ISR(PCINT2_vect)
{
	if (PINK & (1 << 0)){
		PCINTMANAGER::_PCINT_vect[16].setEvent(true);
	}
	else if (PINK & (1 << 1)){
		PCINTMANAGER::_PCINT_vect[17].setEvent(true);
	}
	else if (PINK & (1 << 2)){
		PCINTMANAGER::_PCINT_vect[18].setEvent(true);
	}

	else if (PINK & (1 << 3)){
		PCINTMANAGER::_PCINT_vect[19].setEvent(true);
	}

	else if (PINK & (1 << 4)){
		PCINTMANAGER::_PCINT_vect[20].setEvent(true);
	}

	else if (PINK & (1 << 5)){
		PCINTMANAGER::_PCINT_vect[21].setEvent(true);
	}

	else if (PINK & (1 << 6)){
		PCINTMANAGER::_PCINT_vect[22].setEvent(true);
	}

	else if (PINK & (1 << 7)){
		PCINTMANAGER::_PCINT_vect[23].setEvent(true);
	}

}

