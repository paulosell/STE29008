#include <avr/interrupt.h>
#include "extint.h"
#include "GPIO.h"
#include "pcint.h"
#include "pcintman.h"

GPIO led13(13, GPIO::OUTPUT);
GPIO pin0(10, GPIO::INPUT);

void handler(void){
	led13.set(true);
}

int main( void ){


	PCINTMANAGER manager;
	manager.addPCINT(PCINT::PCINT_10, handler);
	sei();
	while(1){                                   /* forever */
		manager.checkEvents();
	}

	return 0;
}
