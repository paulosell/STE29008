/*
 * STEAV1.cpp
 *
 *  Created on: 20 de mar de 2019
 *      Author: paulosell
 */

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>

#define FOSC 16000000
#define BAUD 9600


void setup1(){

	DDRE &= ~(1 << PE4); // PORT D2 COMO ENTRADA
	DDRE &= ~(1 << PE5); // PORT D3 COMO ENTRADA

	DDRH |= (1 << PH5);  // PORT D8 COMO SAIDA
	DDRH |= (1 << PH6);  // PORT D9 COMO SAIDA

}


void setup2(){
	unsigned int ubrr = (FOSC/16/BAUD)-1;  // Definindo frequencia de oscilamento

	UBRR0H = (unsigned char) (ubrr >> 8);   // Definindo frequencia de
	UBRR0L = (unsigned char) ubrr;		   // Oscilamento

	UCSR0B |= (1 << RXEN0);				   // Habilitando RX0
	UCSR0B |= (1 << TXEN0);				   // Habilitando TX0

	UCSR0C &= ~(1 << USBS0);			   // Definindo numerido de bits e
	UCSR0C |= (3 << UCSZ00);			   // Stop-bit

}

void setup3(){

	ADMUX  |= (1 << REFS0); // Definindo tensão de referencia do conversor
	ADCSRA |= (1 << ADEN);	// Habilitando conversor

}

uint16_t read_adc(uint8_t channel){
	ADMUX |= channel&0x07;   	// Definindo pino de entrada (A5 NO ARDUINO)
	ADCSRB = channel&(1<<3); 	// Definindo bit MUX5 como 0
	ADCSRA |= (1<<ADSC);      	// Inicia nova conversão
	while(ADCSRA & (1<<ADSC));  // Aguarda a conversão finalizar e retorna
	return ADCW;				// Dois bytes com a conversão

}


float RMS (int repeat){

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
	while (true){
		_delay_ms(2000);
		float val = RMS(300);
		float analog_val = (val*5)/1024;
		printf("%.f", double(val));
		char a[10] = "Digital: ";
		char b[12] = "Analogico: ";
		char digital[50];
		char analog[50];

		for (int i = 0; i < 9; i ++){			// Loop para escrever na serial
			while (!( UCSR0A & (1<<UDRE0)));	// A palavra "Digital: "
			UDR0 = (uint8_t) a[i];
		}

		dtostrf(val,5,1, digital);
		dtostrf(analog_val, 3,3,analog);

		for (int i = 0; i < 5; i ++){			 // Loop para escrever os bytes
			while (!( UCSR0A & (1<<UDRE0)));     // Da conversão em valores
			UDR0 = (uint8_t) digital[i];		 // Digitais
		}

		for (int i = 0; i < 11; i ++){			 // Loop para escrever na serial
			while (!( UCSR0A & (1<<UDRE0)));     // A palavra "Analogico: "
			UDR0 = (uint8_t) b[i];
		}

		for (int i = 0; i < 4; i ++){			 // Loop para escrever os bytes
			while (!( UCSR0A & (1<<UDRE0)));     // Da conversão em valores
			UDR0 = (uint8_t) analog[i];			 // Analógicos
		}
	}

}


void exec1(){
	setup1();
	while(true){
		if ((PINE & (1<<PE5))){ 	// O led conectado no bit 6 da PORTH
			PORTH |= (1 << PH6);    // Irá acender quando o quinto bit
		} else {					// Da PORT4 estiver em 1
			PORTH &= ~(1 << PH6);
		}

		if (PINE & (1<<PE4)){		// O led conectado no bit 5 da PORTH irá
			PORTH &= ~(1 << PH5);   // Acender quando o quarto bit da PORT4
		} else {					// Estiver em 0
			PORTH |= (1 << PH5);
		}
	}
}

void exec2(){
	setup2();
	while (true){
		unsigned char byte;
		if ((UCSR0A & (1<<RXC0)) ){   			// Se receber algo pela serial
			byte= UDR0;							// Incrementa o byte e envia
			byte = byte + 1;					// O byte incrementado
			if (( UCSR0A & (1<<UDRE0))){        // Só envia se não ter nada
				UDR0 = byte;					// Na fila de envio
			}
		}
	}
}



void setupINT(){
	DDRE &= ~(1 << PE4);  // Pino D2 do arduino como entrada

	DDRH |= (1 << PH6);   // Pino D9 do arduino como saida

	EICRB = (1 << ISC41); // Definindo a interrupção externo INT4 para ser
	EICRB = (1 << ISC40); // Acionando na borda de subida do sinal
	EIMSK = (1 << INT4);  // Habilitando a interrupção externa INT4
	sei();				  // Habilitando o pino de interrupção global

}
void exec4(){
	setupINT();
	PORTH &= ~(1 << PH6);
	while(true){};


}

void exec5(){
	setupINT();
	PORTH &= ~ (1 << PH6);
	while(true){};
}

void handler_exec4(){
	PORTH ^= (1 << PH6);
}

void handler_exec5(){

	while(((PINE & (1 << PE4)))){
		PORTH &= ~ (1 << PH6);

	}
	PORTH |= (1 << PH6);
}
bool debounce(){
	_delay_ms(100);
	if(PINE & (1 << PE4)){
		return true;
	} else {
		return false;
	}

}
ISR(INT4_vect){
	if(debounce()){
		//handler_exec4();
		handler_exec5();     // trocar handlers de acordo com o exercicio
	}
}
int main(){
	//exec1();
	//exec2();


	//exec3();
	//exec4();
	exec5();
}







