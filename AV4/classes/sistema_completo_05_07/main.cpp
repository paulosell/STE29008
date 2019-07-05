#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "DTMF.h"
#include "uart.h"
#include "Teclado.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "display.h"
#include "EEPROM.h"

//	================================== //
//		   DECLARAÇÃO DO LCD		   //
//  ================================== //

Display lcd;

//	================================== //
//		   DECLARAÇÃO DO DTMF 		   //
//  ================================== //

GPIO c2(43, GPIO::OUTPUT);
GPIO c3(45, GPIO::OUTPUT);
GPIO c4(47, GPIO::OUTPUT);
GPIO c1(49, GPIO::OUTPUT);

GPIO l3(42, GPIO::OUTPUT);
GPIO l2(44, GPIO::OUTPUT);
GPIO l1(46, GPIO::OUTPUT);
GPIO l4(48, GPIO::OUTPUT);

DTMF d(&c1, &c2, &c3, &c4, &l1, &l2, &l3, &l4);

//	================================== //
//		  DECLARAÇÃO DO TECLADO 	   //
//  ================================== //

GPIO l1_t(3, GPIO::OUTPUT);
GPIO l2_t(4, GPIO::OUTPUT);
GPIO l3_t(5, GPIO::OUTPUT);
GPIO l4_t(6, GPIO::OUTPUT);

GPIO c1_t(8, GPIO::INPUT);
GPIO c2_t(9, GPIO::INPUT);
GPIO c3_t(10, GPIO::INPUT);
GPIO c4_t(11, GPIO::INPUT);

Teclado t(&l1_t, &l2_t, &l3_t, &l4_t, &c1_t, &c2_t, &c3_t, &c4_t);

//	================================== //
//		  DECLARAÇÃO DA UART     	   //
//  ================================== //

UART serial((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1,
		UART::ON, UART::UART0);

//	================================== //
//		  DECLARAÇÃO DA EEPROM     	   //
//  ================================== //

EEPROM e;

//	================================== //
//	   DECLARAÇÃO DOS LEDS AUXILIO 	   //
//  ================================== //

GPIO on(15, GPIO::OUTPUT);
GPIO stop(14, GPIO::OUTPUT);

//	==================================================  //
//		  DECLARAÇÃO DAS FUNCOES DO PROJETO     	    //
//  ==================================================  //

void tocar_sequencia();
void gravar_sequencia();
void online();

//	================================== //
//		  DECLARAÇÃO DE CONSTANTES 	   //
//  ================================== //

const unsigned char seq1[] PROGMEM = "123456789";
const unsigned char opcao[] PROGMEM = "Opção selecionada: ";
const unsigned char inicio[] PROGMEM = "A Tocar B Gravar  C Online";

const unsigned char MenuOpcaoAOpcao1[] PROGMEM = "1- seq1  ";
const unsigned char MenuOpcaoAOpcao2[] PROGMEM = "2- seq2 ";
const unsigned char MenuOpcaoAOpcao3[] PROGMEM = "3- seq3 ";
const unsigned char sair[] PROGMEM = "D-sair ";
const unsigned char MenuOpcaoBOpcao1[] PROGMEM = "1- pos2 ";
const unsigned char MenuOpcaoBOpcao2[] PROGMEM = "2- pos3";

const unsigned char MenuOpcaoBGravar[] PROGMEM = "A-gravar ";
const unsigned char gravando[] PROGMEM = "Gravando... ";
const unsigned char digite[] PROGMEM = "Digite:";

const unsigned char MenuPrincipalOpcaoC[] PROGMEM
		= "Digite C para o modo online\n";
const unsigned char MenuOpcaoCIn[] PROGMEM = "Online!! D- sair";
const unsigned char MenuOpcaoCOut[] PROGMEM = "Saindo do modo online\n";

uint8_t * pos_inicio = 0;
uint8_t dado = 0;

int main(void) {
	sei();
	on.set(true);
	stop.set(false);

	e.write(pos_inicio, 1);
	e.write(pos_inicio + 1, 1);

	while (true) {
		lcd.clear_display();
		for (unsigned int i = 0; i < sizeof(inicio) - 1; i++) {
			lcd.escreve_LCD(pgm_read_byte(&inicio[i]));
			if (i == 15)
				lcd.quebra_linha();
		}

		while (t.varredura())
			;
		uint8_t tecla = t.getTecla();

		if (tecla == 20) {
			for (unsigned int i = 0; i < sizeof(opcao); i++) {
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			tocar_sequencia();
		}

		if (tecla == 21) {
			for (unsigned int i = 0; i < sizeof(opcao); i++) {
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			gravar_sequencia();
		}

		if (tecla == 22) {
			for (unsigned int i = 0; i < sizeof(opcao); i++) {
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			online();
		}
	}

}

void tocar_sequencia() {
	lcd.clear_display();
	while (true) {
		for (unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao1) - 1; i++) {
			lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoAOpcao1[i]));
		}

		if (e.read(pos_inicio) == 1 && e.read(pos_inicio + 1) == 1) {
			for (unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao2) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoAOpcao2[i]));
			}

			lcd.quebra_linha();
			for (unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao3) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoAOpcao3[i]));
			}

			for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&sair[i]));
			}

			while (t.varredura())
				;
			uint8_t tecla = t.getTecla();

			if (tecla == 1) {
				uint8_t digitos[sizeof(seq1)];
				serial.put(0x31);
				for (unsigned int i = 0; i < sizeof(seq1); i++) {
					digitos[i] = pgm_read_byte(&seq1[i]);

				}
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(digitos); i++) {
					lcd.escreve_LCD(digitos[i]);
					d.send_dtmf(digitos[i] - 0x30);
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 2) {
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (int i = 0; i < 10; i++) {
					lcd.escreve_LCD(e.read(i + pos_inicio + 20) + 0x30);
					d.send_dtmf(e.read(i + pos_inicio + 20));
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 3) {
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (int i = 0; i < 10; i++) {
					lcd.escreve_LCD(e.read(i + pos_inicio + 40) + 0x30);
					d.send_dtmf(e.read(i + pos_inicio + 40));
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 23) {
				return;

			}

		} else if (e.read(pos_inicio) == 1) {

			for (unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao2) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoAOpcao2[i]));
			}

			lcd.quebra_linha();
			for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&sair[i]));
			}

			while (t.varredura())
				;
			uint8_t tecla = t.getTecla();
			if (tecla == 1) {
				uint8_t digitos[sizeof(seq1)];
				serial.put(0x31);
				for (unsigned int i = 0; i < sizeof(seq1); i++) {
					digitos[i] = pgm_read_byte(&seq1[i]);

				}
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(digitos); i++) {
					lcd.escreve_LCD(digitos[i]);
					d.send_dtmf(digitos[i] - 0x30);
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 2) {
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (int i = 0; i < 10; i++) {
					lcd.escreve_LCD(e.read(i + pos_inicio + 20) + 0x30);
					d.send_dtmf(e.read(i + pos_inicio + 20));
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 23) {
				return;

			}

		} else if (e.read(pos_inicio + 1) == 1) {

			for (unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao3) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoAOpcao3[i]));
			}

			lcd.quebra_linha();

			for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&sair[i]));
			}

			while (t.varredura())
				;
			uint8_t tecla = t.getTecla();
			if (tecla == 1) {
				uint8_t digitos[sizeof(seq1)];
				serial.put(0x31);
				for (unsigned int i = 0; i < sizeof(seq1); i++) {
					digitos[i] = pgm_read_byte(&seq1[i]);

				}
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(digitos); i++) {
					lcd.escreve_LCD(digitos[i]);
					d.send_dtmf(digitos[i] - 0x30);
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 3) {
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (int i = 0; i < 10; i++) {
					lcd.escreve_LCD(e.read(i + pos_inicio + 20) + 0x30);
					d.send_dtmf(e.read(i + pos_inicio + 20));
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			else if (tecla == 23) {
				return;

			}

		} else {

			while (t.varredura())
				;
			uint8_t tecla = t.getTecla();
			if (tecla == 1) {
				uint8_t digitos[sizeof(seq1)];
				serial.put(0x31);
				for (unsigned int i = 0; i < sizeof(seq1); i++) {
					digitos[i] = pgm_read_byte(&seq1[i]);

				}
				on.toggle();
				stop.toggle();
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(digitos); i++) {
					lcd.escreve_LCD(digitos[i]);
					d.send_dtmf(digitos[i] - 0x30);
					_delay_ms(1000);
				}
				on.toggle();
				stop.toggle();
				return;
			}

			if (tecla == 23) {
				return;

			}

		}

	}
}
void online() {

	lcd.clear_display();
	for (unsigned int i = 0; i < sizeof(MenuOpcaoCIn) - 1; i++) {
		lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoCIn[i]));
	}

	lcd.quebra_linha();

	bool flag = false;
	on.toggle();
	stop.toggle();
	int a = 0;
	while (!flag) {

		while (t.varredura())
			;

		uint8_t tecla = t.getTecla();
		if (tecla == 1 || tecla == 2 || tecla == 3 || tecla == 4 || tecla == 5
				|| tecla == 6 || tecla == 7 || tecla == 8 || tecla == 9
				|| tecla == 0) {
			a++;
			if (a == 16) {
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(MenuOpcaoCIn)-1; i++) {
					lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoCIn[i]));
				}

				lcd.quebra_linha();
				a = 0;
			}
			lcd.escreve_LCD(tecla + 0x30);

			d.send_dtmf(tecla);
		} else if (tecla == 23) {
			flag = true;
		}

	}
	on.toggle();
	stop.toggle();


}

void gravar_sequencia() {
	bool flag = true;
	while (flag) {
		lcd.clear_display();
		for (unsigned int i = 0; i < sizeof(MenuOpcaoBOpcao1) - 1; i++) {
			lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoBOpcao1[i]));
		}

		for (unsigned int i = 0; i < sizeof(MenuOpcaoBOpcao2) - 1; i++) {
			lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoBOpcao2[i]));
		}

		lcd.quebra_linha();
		for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
			lcd.escreve_LCD(pgm_read_byte(&sair[i]));
		}

		while (t.varredura())
			;
		uint8_t pos = t.getTecla();

		if (pos == 1 || pos == 2) {
			for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
				serial.put(pgm_read_byte(&sair[i]));
			}

			Fila<uint8_t, 10> digitos;
			lcd.clear_display();

			for (unsigned int i = 0; i < sizeof(gravando) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&gravando[i]));
			}

			lcd.quebra_linha();

			while (!digitos.cheia()) {
				while (t.varredura())
					;
				uint8_t tecla;
				tecla = t.getTecla();

				if ((tecla == 1 || tecla == 2 || tecla == 3 || tecla == 4
						|| tecla == 5 || tecla == 6 || tecla == 7 || tecla == 8
						|| tecla == 9 || tecla == 0)) {
					lcd.escreve_LCD(tecla + 0x30);
					digitos.push(tecla);
				}

			}

			lcd.clear_display();

			for (unsigned int i = 0; i < sizeof(MenuOpcaoBGravar) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&MenuOpcaoBGravar[i]));
			}

			lcd.quebra_linha();
			for (unsigned int i = 0; i < sizeof(sair) - 1; i++) {
				lcd.escreve_LCD(pgm_read_byte(&sair[i]));
			}

			while (t.varredura())
				;
			uint8_t tecla;
			tecla = t.getTecla();

			if (tecla == 20) {
				lcd.clear_display();
				for (unsigned int i = 0; i < sizeof(gravando) - 1; i++) {
					lcd.escreve_LCD(pgm_read_byte(&gravando[i]));
				}
				on.toggle();
				stop.toggle();
				_delay_ms(1000);
				on.toggle();
				stop.toggle();

				if (pos == 1) {
					e.write_burst(pos_inicio + 20, digitos);
					e.write(pos_inicio, 1);
				}
				if (pos == 2) {
					e.write_burst(pos_inicio + 40, digitos);
					e.write(pos_inicio + 1, 1);
				}
			} else if (tecla == 23) {
				break;
			}
		}

		if (pos == 23) {
			flag = false;
		}

	}

}
;

