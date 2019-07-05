/*
 * Teclado.cpp
 *
 *  Created on: 26/06/2019
 *      Author: aluno
 */


#include "Teclado.h"

Teclado::Teclado(GPIO *l1, GPIO *l2, GPIO *l3, GPIO *l4
		, GPIO *c1, GPIO *c2, GPIO *c3, GPIO *c4){

	linhas[0] = l1;
	linhas[1] = l2;
	linhas[2] = l3;
	linhas[3] = l4;

	colunas[0] = c1;
	colunas[1] = c2;
	colunas[2] = c3;
	colunas[3] = c4;
	linha = 200;
	coluna = 200;
}

bool Teclado::varredura(){
	bool pressed = true;
	for (int i = 0; i < 4; i++){
		linhas[0]->set(false);
		linhas[1]->set(false);
		linhas[2]->set(false);
		linhas[3]->set(false);
		linhas[i]->set(true);

		if(colunas[0]->get()){
			linha = i;
			coluna = 0;
			while(colunas[0]->get())
			pressed = false;
		}

		if(colunas[1]->get()){
			linha = i;
			coluna = 1;
			while(colunas[1]->get())
			pressed = false;
		}

		if(colunas[2]->get()){

			linha = i;
			coluna = 2;
			while(colunas[2]->get())
			pressed = false;
		}

		if(colunas[3]->get()){
			linha = i;
			coluna = 3;
			while(colunas[3]->get())
			pressed = false;
		}

	}
	return pressed;
}

uint8_t Teclado::getTecla(){
	uint8_t tecla;
	if (linha == 0 && coluna == 0){
		tecla = 1;
	}

	if (linha == 0 && coluna == 1){
		tecla =  2;
	}

	if (linha == 0 && coluna == 2){
		tecla = 3;
	}

	if (linha == 1 && coluna == 0){
		tecla = 4;
	}

	if (linha == 1 && coluna == 1){
		tecla = 5;
	}

	if (linha == 1 && coluna == 2){
		tecla = 6;
	}

	if (linha == 2 && coluna == 0){
		tecla = 7;
	}

	if (linha == 2 && coluna == 1){
		tecla = 8;
	}

	if (linha == 2 && coluna == 2){
		tecla = 9;
	}

	if (linha == 0 && coluna == 3){
		tecla = 20;
	}

	if (linha == 1 && coluna == 3){
		tecla = 21;
	}

	if (linha == 2 && coluna == 3){
		tecla = 22;
	}

	if (linha == 3 && coluna == 3){
		tecla = 23;
	}

	if (linha == 3 && coluna == 2){
		tecla = 0;
	}

	return tecla;
}

