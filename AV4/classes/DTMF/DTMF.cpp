/*
 * DTMF.cpp
 *
 *  Created on: 25 de jun de 2019
 *      Author: paulosell
 */

#include "DTMF.h"
#include "GPIO.h"
#include <util/delay.h>

DTMF::DTMF(GPIO * c1, GPIO * c2, GPIO * c3, GPIO * c4, GPIO *l1,
		GPIO * l2, GPIO * l3, GPIO * l4){
	colunas[0] = c1;
	colunas[1] = c2;
	colunas[2] = c3;
	colunas[3] = c4;

	linhas[0] = l1;
	linhas[1] = l2;
	linhas[2] = l3;
	linhas[3] = l4;

	for (int i = 0; i < 4; i++){
		linhas[i]->set(true);
		colunas[i]->set(true);
	}
}

void DTMF::send_dtmf(DTMF_t digito){
	int delay = 15000;
	switch(digito){
	case 0:
		linhas[3]->toggle();
		colunas[1]->toggle();
		_delay_ms(delay);
		linhas[3]->toggle();
		colunas[1]->toggle();
		break;

	case 1:
		linhas[0]->toggle();
		colunas[0]->toggle();
		_delay_ms(delay);
		linhas[0]->toggle();
		colunas[0]->toggle();
		break;

	case 2:
		linhas[0]->toggle();
		colunas[1]->toggle();
		_delay_ms(delay);
		linhas[0]->toggle();
		colunas[1]->toggle();
		break;

	case 3:
		linhas[0]->toggle();
		colunas[2]->toggle();
		_delay_ms(delay);
		linhas[0]->toggle();
		colunas[2]->toggle();
		break;

	case 4:
		linhas[1]->toggle();
		colunas[0]->toggle();
		_delay_ms(delay);
		linhas[1]->toggle();
		colunas[0]->toggle();
		break;
	case 5:
		linhas[1]->toggle();
		colunas[1]->toggle();
		_delay_ms(delay);
		linhas[1]->toggle();
		colunas[1]->toggle();
		break;

	case 6:
		linhas[1]->toggle();
		colunas[2]->toggle();
		_delay_ms(delay);
		linhas[1]->toggle();
		colunas[2]->toggle();
		break;

	case 7:
		linhas[2]->toggle();
		colunas[0]->toggle();
		_delay_ms(delay);
		linhas[2]->toggle();
		colunas[0]->toggle();
		break;

	case 8:
		linhas[2]->toggle();
		colunas[1]->toggle();
		_delay_ms(delay);
		linhas[2]->toggle();
		colunas[1]->toggle();
		break;

	case 9:
		linhas[2]->toggle();
		colunas[2]->toggle();
		_delay_ms(delay);
		linhas[2]->toggle();
		colunas[2]->toggle();
		break;

	case 10:
		linhas[3]->toggle();
		colunas[0]->toggle();
		_delay_ms(delay);
		linhas[3]->toggle();
		colunas[0]->toggle();
		break;

	case 11:
		linhas[3]->toggle();
		colunas[2]->toggle();
		_delay_ms(delay);
		linhas[3]->toggle();
		colunas[2]->toggle();
		break;
	}



}


