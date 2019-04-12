/*
 * uart.h
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdlib.h>

class UART{
public:
	enum DATABITS_t{
		DATABITS_5 = 0,
		DATABITS_6 = 2,
		DATABITS_7 = 4,
		DATABITS_8 = 6
	};

	enum PARITY_t{
		NONE = 0,
		EVEN = 32,
		ODD = 48
	};

	enum STOPBITS_t{
		STOPBIT_1 = 0,
		STOPBIT_2 = 8
	};

	UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb);
	~UART(){};

	void put(uint8_t data);
	void puts(char data[]);
    uint8_t get();
    bool ableToGet();
    bool ableToPut();

private:
    unsigned int getUBRR(uint32_t baud);


};


#endif /* UART_H_ */
