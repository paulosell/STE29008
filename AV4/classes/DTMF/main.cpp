#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "DTMF.h"


GPIO c2(23 , GPIO::OUTPUT);
GPIO c3(25 , GPIO::OUTPUT);
GPIO c4(27 , GPIO::OUTPUT);
GPIO c1(29 , GPIO::OUTPUT);

GPIO l3(22 , GPIO::OUTPUT);
GPIO l2(24 , GPIO::OUTPUT);
GPIO l1(26 , GPIO::OUTPUT);
GPIO l4(28 , GPIO::OUTPUT);

	DTMF d(&c1, &c2, &c3, &c4, &l1, &l2, &l3, &l4);

int main(void){

	UCSR0B = 0;

	while(true){
	d.send_dtmf(DTMF::DIGITO_cerca);

	}

}
