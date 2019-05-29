/*
 * main.cpp
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

char you_send[] = "You send through UART :  \n";
char echo[] = "Echo:  \n";
int main(){




	UART uart0((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART0);
	UART uart1((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART1);
	UART uart2((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART2);
	UART uart3((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART3);
	sei();
	char data0[] = "ola uart0";
	char data1[] = "ola uart1";
	char data2[] = "ola uart2";
	char data3[] = "ola uart3";

	uart0.puts(data0, sizeof(data0)-1);
	uart1.puts(data1, sizeof(data1)-1);
	uart2.puts(data2, sizeof(data2)-1);
	uart3.puts(data3, sizeof(data3)-1);


		while(true){
			if(uart0.hasData()){
				uint8_t data = uart0.get();
				uart0.put(data);
				uart1.put(data);
				uart2.put(data);
				uart3.put(data);
			}

			if(uart1.hasData()){
				uint8_t data = uart1.get();
				uart0.put(data);
				uart1.put(data);
				uart2.put(data);
				uart3.put(data);
			}

			if(uart2.hasData()){
				uint8_t data = uart2.get();
				uart0.put(data);
				uart1.put(data);
				uart2.put(data);
				uart3.put(data);
			}

			if(uart3.hasData()){
				uint8_t data = uart3.get();
				uart0.put(data);
				uart1.put(data);
				uart2.put(data);
				uart3.put(data);
			}
		}



}
