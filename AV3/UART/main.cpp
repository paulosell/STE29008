/*
 * main.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
int main(){

	UART serial((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
	sei();
	while(true){
		if(serial.hasData()){
			uint8_t data = serial.get();
			serial.put(data);
			serial.put(data+1);
			serial.put(data+2);
			serial.put(data+3);
			serial.put(data+4);
			serial.put(data+5);
			serial.put(data+6);
			serial.put(data+7);
			serial.put(data+8);
			serial.put(data+9);
			serial.put(data+10);


		}


}
}
