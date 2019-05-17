/*
 * pcint.h
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */

#ifndef PCINT_H_
#define PCINT_H_

#include <stdio.h>
#include "GPIO.h"
#include <avr/interrupt.h>

typedef void (*CALLBACK_t)(void);
class PCINT{
public:
	enum PCINT_ID_t{
		PCINT_0 = 0,
		PCINT_1 = 1,
		PCINT_2 = 2,
		PCINT_3 = 3,
		PCINT_4 = 4,
		PCINT_5 = 5,
		PCINT_6 = 6,
		PCINT_7 = 7,
		PCINT_8 = 8,
		PCINT_9 = 9,
		PCINT_10 = 10,
		PCINT_11 = 11,
		PCINT_12 = 12,
		PCINT_13 = 13,
		PCINT_14 = 14,
		PCINT_15 = 15,
		PCINT_16 = 16,
		PCINT_17 = 17,
		PCINT_18 = 18,
		PCINT_19 = 19,
		PCINT_20 = 20,
		PCINT_21 = 21,
		PCINT_22 = 22,
		PCINT_23 = 23
	};
	PCINT();
	void enable(PCINT_ID_t id);
	void disable(PCINT_ID_t id);
	void callback(){(*_pCallback)();}
	void setEvent(bool event);
	bool event();
	void setCallback(CALLBACK_t callback);
private:
	CALLBACK_t _pCallback;
	bool _event;
};



#endif /* PCINT_H_ */
