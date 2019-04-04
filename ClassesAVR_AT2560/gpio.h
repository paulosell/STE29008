/*
 * gpio.h
 *
 *  Created on: 03/04/2019
 *      Author: aluno
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <stdio.h>




class GPIO {
public:
	enum PortDirection_t{
		INPUT,
		OUTPUT
	};

	GPIO(int id, PortDirection_t dir);
	~GPIO();

	bool read();
	void write(bool val=1);
	void toggle();

private:
	uint8_t _bit;
	volatile uint8_t* _DDR;
	volatile uint8_t* _PIN;
	volatile uint8_t* _PORT;



};


#endif /* GPIO_H_ */
