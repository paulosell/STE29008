/*
 * UART_Mapper.h
 *
 *  Created on: 25 de mai de 2019
 *      Author: paulosell
 */

#ifndef UART_MAPPER_H_
#define UART_MAPPER_H_
#include <stdio.h>
#include <stdlib.h>
namespace UART_MAPPER{

class UART_Mapper{
public:

	uint8_t getUDR();
	void enableInt();
	void disableInt();
	void setUDR(uint8_t data);
	void setUART(uint32_t baud, uint8_t parity, uint8_t db, uint8_t sb, uint8_t ds);
private:

	uint8_t UCSRA;
	uint8_t UCSRB;
	uint8_t UCSRC;
	uint8_t reserved;
	uint8_t UBRRL;
	uint8_t UBRRH;
	uint8_t UDR;
};
	extern UART_Mapper * AllUarts[4];
}



#endif /* UART_MAPPER_H_ */
