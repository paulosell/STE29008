/*
 * Teclado.h
 *
 *  Created on: 26/06/2019
 *      Author: aluno
 */

#ifndef TECLADO_H_
#define TECLADO_H_
#include "GPIO.h"
class Teclado{

public:
	Teclado(GPIO *l1,GPIO *l2,GPIO *l3,GPIO *l4
			,GPIO *c1, GPIO *c2, GPIO *c3, GPIO *c4);

	~Teclado(){};
	bool varredura();
	uint8_t getTecla();

private:
	GPIO *linhas[4];
	GPIO *colunas[4];
	uint8_t linha;
	uint8_t coluna;
};


#endif /* TECLADO_H_ */
