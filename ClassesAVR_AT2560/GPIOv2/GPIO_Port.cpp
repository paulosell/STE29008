/*
 * GPIO_Port.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */
#include "GPIO_Port.h"

namespace GPIO_PORT {

enum PORT_ADDR_BASE {
    AVR_PB = 0x0023,
    AVR_PC = 0x0026,
    AVR_PD = 0x0029,
	AVR_PE = 0x002C,
	AVR_PH = 0x0100,
	AVR_PG = 0x0032
};

GPIO_Port * PB = reinterpret_cast<GPIO_Port*>(AVR_PB);
GPIO_Port * PC = reinterpret_cast<GPIO_Port*>(AVR_PC);
GPIO_Port * PD = reinterpret_cast<GPIO_Port*>(AVR_PD);
GPIO_Port * PE = reinterpret_cast<GPIO_Port*>(AVR_PE);
GPIO_Port * PG = reinterpret_cast<GPIO_Port*>(AVR_PG);
GPIO_Port * PH = reinterpret_cast<GPIO_Port*>(AVR_PH);

//GPIO_Port * portB = (GPIO_Port *)AVR_PORTB;
//GPIO_Port * portD = (GPIO_Port *)AVR_PORTD;


void GPIO_Port::dir(int p, int io) {
    if (io)
        ddr |= (1 << p);
    else
        ddr &= ~(1 << p);
}
void GPIO_Port::set(int p, int val) {
    if (val)
        port |= (1 << p);
    else
        port &= ~(1 << p);
}
void GPIO_Port::clear(int p) {
    set(p,0);
}
int GPIO_Port::get(int p) {
    return pin & (1 << p);
}

void GPIO_Port::toggle(int p) {
	pin = (1 << p);
}


} /* namespace GPIO_PORT */
