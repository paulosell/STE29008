/*
 * uart.h
 *
 *  Created on: 12/04/2019
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_

#include "UART_Mapper.h"
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

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

	enum DOUBLESPEED_t{
		OFF = 0,
		ON = 1
	};

	enum UARTID_t{
		UART0 = 0,
		UART1 = 1,
		UART2 = 2,
		UART3 = 3
	};

	UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb, DOUBLESPEED_t ds, UARTID_t id);
	~UART(){};

	void put(uint8_t data);
	void puts(char data[], int len);
    uint8_t get();
    static void rxHandler(uint8_t id);
    static void txHandler(uint8_t id);
    bool hasData();
    UART_MAPPER::UART_Mapper * _uartptr;

    bool _has_data;

    Fila<uint8_t, 10> _rx;
    Fila<uint8_t, 10> _tx;
    uint8_t _id;
private:

    static UART * uarts_singletons[4];



};



#endif /* UART_H_ */
