/*
 * EXTINT.h
 *
 *  Created on: 26/04/2019
 *      Author: aluno
 */

#ifndef EXTINT_H_
#define EXTINT_H_

#include <stdio.h>
#include <avr/interrupt.h>

typedef void (*CALLBACK_t)(void);
class EXTINT{
public:
	enum INT_ID_t{
		INT_0 = 0,
		INT_1 = 1,
		INT_2 = 2,
		INT_3 = 3,
		INT_4 = 4,
		INT_5 = 5,
		INT_6 = 6,
		INT_7 = 7
	};

	enum ISC_t{
		LOW_LEVEL = 1,
		ANY_EDGE = 2,
		FALLING = 3,
		RISING = 4
	};

	EXTINT(INT_ID_t id, ISC_t edge, CALLBACK_t callback);
	void enable();
	void disable();
	void callback(){(*_pCAllback)();}
	static EXTINT * _EXTINT_singletons[8];

private:
	uint8_t _id;
	CALLBACK_t _pCAllback;


};




#endif /* EXTINT_H_ */
