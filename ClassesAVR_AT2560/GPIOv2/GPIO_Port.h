/*
 * GPIO_Port.h
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */

#ifndef GPIO_PORT_H_
#define GPIO_PORT_H_

#include <avr/io.h>

namespace GPIO_PORT {

class GPIO_Port {
public:
    void dir(int p, int io);
    void set(int p, int val = 1);
    void clear(int p);
    int get(int p);
    void toggle(int p);

private:
    unsigned char pin;
    unsigned char ddr;
    unsigned char port;
};

extern GPIO_Port * PB;
extern GPIO_Port * PC;
extern GPIO_Port * PD;
extern GPIO_Port * PE;
extern GPIO_Port * PH;
extern GPIO_Port * PG;

} /* namespace GPIO_PORT */
#endif /* GPIO_PORT_H_ */
