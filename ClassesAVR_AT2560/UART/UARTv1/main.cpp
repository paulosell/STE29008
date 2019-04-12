/*
 * main.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */


#include "uart.h"

int main(){

	UART serial((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1);
	while(true){
		if(serial.ableToGet()){
			uint8_t read = serial.get();
			if(serial.ableToPut()){
				serial.put(read);
			}
	}




}
}
