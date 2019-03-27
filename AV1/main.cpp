/*
 * STEAV1.cpp
 *
 *  Created on: 20 de mar de 2019
 *      Author: paulosell
 */

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#define FOSC 16000000
#define BAUD 9600
#define myubrr (FOSC/16/BAUD)-1
void setup1(){

	DDRE &= ~(1 << 4); // PORT D2 AS INPUT
	DDRE &= ~(1 << 5); // PORT D3 AS INPUT

	DDRH |= (1 << 5); // PORT D8 AS OUTPUT
	DDRH |= (1 << 6); // PORT D9 AS OUTPUT

}


void setup2(){
	unsigned int ubrr = (FOSC/16/BAUD)-1;

	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;

	UCSR0B |= (1 << RXEN0);
	UCSR0B |= (1 << TXEN0);

	UCSR0C &= ~(1 << USBS0);
	UCSR0C |= (3 << UCSZ00);

}

void setup3(){
	ADCSRA |= (1 << ADPS2);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);

	ADMUX  |= (1 << REFS0);
	ADCSRA |= (1 << ADEN);

}

float read_adc(uint8_t channel){
	ADMUX &= 0xE0;           //Clear bits MUX0-4
	ADMUX |= channel&0x07;   //Defines the new ADC channel to be read by setting bits MUX0-2
	ADCSRB = channel&(1<<3); //Set MUX5
	ADCSRA |= (1<<ADSC);      //Starts a new conversion
	while(ADCSRA & (1<<ADSC));  //Wait until the conversion is done
	return ADCW;

}         //Returns the ADC value of the chosen channel


int RMS (int repeat){

	float accumulated = 0;
	float average;
	float digital_value;
	uint8_t channel = 5;
	for (int i = 0; i < repeat; i++){
		digital_value = read_adc(channel);
		accumulated = accumulated + (digital_value*digital_value);


	}

	average = accumulated/repeat;

	return sqrt(average);


}
void exec3(){
	setup3();
	setup2();

	float val = RMS(30);
	float analog_val = (val*5)/1024;
	printf("%.f", double(val));
	char a[10] = "Digital: ";
	char b[12] = "Analogico: ";

	for (int i = 0; i < 10; i ++){

		while ( !( UCSR0A & (1<<UDRE0)) )  ;
		UDR0 = (uint8_t) a[i];


	}

	while ( !( UCSR0A & (1<<UDRE0)) )  ;
	UDR0 = (uint8_t)val + 0x30;

	for (int i = 0; i < 12; i ++){

		while ( !( UCSR0A & (1<<UDRE0)) )  ;
		UDR0 = (uint8_t) b[i];


	}


	while ( !( UCSR0A & (1<<UDRE0)) )  ;
	UDR0 = (uint8_t)analog_val;












}

void controleBotao5V(){
	// O led conectado no bit 6 da PORTH irá acender
	// Quando o quinto bit da PORT4 estiver em 1
	if (PINE & (1<<5)){
		PORTH |= (1 << 6);

	}
	else {
		PORTH &= ~(1 << 6);
	}

}

void controleBotao0V(){
	// O led conectado no bit 5 da PORTH irá acender
	// Quando o quarto bit da PORT4 estiver em 0
	if (PINE & (1<<4)){
		PORTH &= ~(1 << 5);

	}
	else {
		PORTH |= (1 << 5);
	}

}
void exec1(){

	setup1();
	while(true){
		controleBotao5V();
		controleBotao0V();
	}
}

void exec2(){
	setup2();
	while (true){

		unsigned char byte;
		if ( (UCSR0A & (1<<RXC0)) ){
			byte= UDR0;
			byte = byte + 1;

			if ( ( UCSR0A & (1<<UDRE0)) )   {
				UDR0 = byte;
			}
		}
	}
}


int main(){
	//exec1();
	//exec2();


	exec3();


}





