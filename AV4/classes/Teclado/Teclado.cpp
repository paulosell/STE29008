/*
 * Teclado.cpp
 *
 *  Created on: 26/06/2019
 *      Author: aluno
 */


#include "Teclado.h"

Teclado::Teclado(GPIO *l1,GPIO *l2,GPIO *l3,GPIO *l4
		,GPIO *c1, GPIO *c2, GPIO *c3, GPIO *c4){

	linhas[0] = l1;
	linhas[1] = l2;
	linhas[2] = l3;
	linhas[3] = l4;

	colunas[0] = c1;
	colunas[1] = c2;
	colunas[2] = c3;
	colunas[3] = c4;
}

