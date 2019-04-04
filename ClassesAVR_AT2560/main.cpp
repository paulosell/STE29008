/*
 * main.cpp
 *
 *  Created on: 03/04/2019
 *      Author: aluno
 */


#include "gpio.h"

#include <util/delay.h>



int main(){

	GPIO d2(2, GPIO::OUTPUT);
	GPIO d3(3, GPIO::OUTPUT);
	GPIO d4(4, GPIO::OUTPUT);
	GPIO d5(5, GPIO::OUTPUT);
	GPIO d6(6, GPIO::OUTPUT);
	GPIO d7(7, GPIO::OUTPUT);
	GPIO d8(8, GPIO::OUTPUT);
	GPIO d9(9, GPIO::OUTPUT);

	while(true){
		d2.toggle();
		_delay_ms(500);

		d3.toggle();
		_delay_ms(500);

		d4.toggle();
		_delay_ms(500);

		d5.toggle();
		_delay_ms(500);

		d6.toggle();
		_delay_ms(500);

		d7.toggle();
		_delay_ms(500);

		d8.toggle();
		_delay_ms(500);

		d9.toggle();
		_delay_ms(500);

	}

}
