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


GPIO p2(2, GPIO::OUTPUT);
GPIO p3(3, GPIO::OUTPUT);
GPIO p4(4, GPIO::OUTPUT);
GPIO p5(5, GPIO::OUTPUT);
void timeout2_handler(void){
	p2.toggle();
}

void timeout3_handler(void){
	p3.toggle();
}


void timeout4_handler(void){
	p4.toggle();
}

void timeout5_handler(void){
	p5.toggle();
}


Timer t = Timer(1000);



int main(){

	sei();
	t.addTimeout(1000, &timeout2_handler);
	t.addTimeout(2000, &timeout3_handler);
	t.addTimeout(3000, &timeout4_handler);
	t.addTimeout(4000, &timeout5_handler);
	while(true){
		t.timeoutManager();
}
}
