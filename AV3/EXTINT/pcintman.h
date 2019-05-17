/*
 * pcintman.h
 *
 *  Created on: 17 de mai de 2019
 *      Author: aluno
 */

#ifndef PCINTMAN_H_
#define PCINTMAN_H_
#include "pcint.h"


class PCINTMANAGER{
public:
	PCINTMANAGER();
	void addPCINT(PCINT::PCINT_ID_t id, CALLBACK_t callback);
	void checkEvents();
	void disable(PCINT::PCINT_ID_t id);
	void enable(PCINT::PCINT_ID_t id);
	static PCINT _PCINT_vect[24];
private:

};


#endif /* PCINTMAN_H_ */
