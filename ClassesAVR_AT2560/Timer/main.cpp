/*
 * main.cpp
 *
 *  Created on: 08/05/2019
 *      Author: aluno
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "Timer.h"

GPIO p13(13, GPIO::OUTPUT);
void timeout_handler(void){
	p13.toggle();
}

Timer t = Timer(1000);



int main(){

	sei();
	t.addTimeout(1000, &timeout_handler);
	while(true){
		t.delay(1000);
		p13.toggle();

		//t.timeoutManager();
}
}
