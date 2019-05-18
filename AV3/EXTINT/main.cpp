#include <avr/interrupt.h>
#include "GPIO.h"
#include "pcintman.h"

GPIO led13(13, GPIO::OUTPUT);
GPIO pin1(14, GPIO::INPUT);
PCINTMANAGER manager;
void handler(void){
	led13.toggle();

}

int main( void ){

	manager.addPCINT(PCINT::PCINT_10, &handler);
	sei();
	while(1){                                   /* forever */
		manager.checkEvents();

	}

	return 0;
}
