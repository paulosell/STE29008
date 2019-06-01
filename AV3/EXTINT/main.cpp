#include <avr/interrupt.h>
#include "GPIO.h"
#include "pcintman.h"

GPIO pin6(6, GPIO::OUTPUT);
GPIO pin7(7, GPIO::OUTPUT);

GPIO pin14(14, GPIO::INPUT);
GPIO pin15(15, GPIO::INPUT);

PCINTMANAGER manager;

void handler_14(void){
	pin6.toggle();

}

void handler_15(void){
	pin7.toggle();

}

int main( void ){

	manager.addPCINT(PCINT::PCINT_10, &handler_14);
	manager.addPCINT(PCINT::PCINT_9, &handler_15);
	sei();
	while(1){                                   /* forever */
		manager.checkEvents();

	}

	return 0;
}
