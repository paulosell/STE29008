#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
 
 

int main(void){
	GPIO led2(2, GPIO::OUTPUT);
	GPIO led3(3, GPIO::OUTPUT);
	GPIO led4(4, GPIO::OUTPUT);
	GPIO led5(5, GPIO::OUTPUT);
	GPIO led6(6, GPIO::OUTPUT);
	GPIO led7(7, GPIO::OUTPUT);
	GPIO led8(8, GPIO::OUTPUT);
	GPIO led9(9, GPIO::OUTPUT);

	led2.set(true);
	led3.set(false);
	led4.set(true);
	led5.set(false);
	led6.set(true);
	led7.set(false);
	led8.set(true);
	led9.set(false);




	while (1){
		led2.toggle();
		led5.toggle();
		led4.toggle();

		_delay_ms(100);
		led7.toggle();
		led9.toggle();
		_delay_ms(200);
		led3.toggle();
		led6.toggle();
		led8.toggle();
		_delay_ms(100);



	}
 
}
