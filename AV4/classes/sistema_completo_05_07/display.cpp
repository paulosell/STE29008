#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "display.h"

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

#define DADOS_LCD PORTA
#define CONTR_LCD PORTB
#define RS PB1
#define E PB0

//const unsigned char menuA[] PROGMEM = "Digite A para selecionar uma sequência";
//const unsigned char menuB[] PROGMEM = "Digite B para gravar uma sequência";
//const unsigned char menuC[] PROGMEM = "Digite C para modo online";
//const unsigned char menuAa[] PROGMEM = "Selecione a sequencia (1, 2 ou 3)";
//const unsigned char menuBa[] PROGMEM = "Selecione a posicao (1, 2 ou 3)";
//const unsigned char menuCa[] PROGMEM = "Modo online";
//const unsigned char cancelar[] PROGMEM = "Cancelar";

void Display::pulso_enable() {
	_delay_us(1);
	set_bit(CONTR_LCD,E);
	_delay_us(1);
	clr_bit(CONTR_LCD,E);
	_delay_us(45);
}

//void Display::read_progmem(const unsigned char *msg) {
//	unsigned char i;
//	int tam = sizeof(msg);
//	for (i = 0; i < 32; i++){
//		if (i == tam) {
//			break;
//		}
//		if (i == 16) {
//				write_cmd(0xC0, 0);
//		}
//		write_cmd(pgm_read_byte(&msg[i]), 1);
//	}
//}


void Display::write_cmd(unsigned char c, char cd) {
	DADOS_LCD = c;
	if (cd == 0)
		clr_bit(CONTR_LCD, RS);
	else
		set_bit(CONTR_LCD, RS);
	pulso_enable();
	if ((cd == 0) && (c < 4))
		_delay_ms(2);
}

void Display::init_display()
{
	clr_bit(CONTR_LCD, RS);
	_delay_ms(15);
	DADOS_LCD = 0x38;
	pulso_enable();
	_delay_ms(5);
	pulso_enable();
	_delay_us(200);
	pulso_enable();
	pulso_enable();
	write_cmd(0x08, 0);
	write_cmd(0x01, 0);
	write_cmd(0x0C, 0);
	write_cmd(0x80, 0);
	write_cmd(0x80, 0);
}



void Display::escreve_LCD(uint8_t c) {

		write_cmd(c, 1);

}

void Display::quebra_linha(){

	write_cmd(0xC0, 0);

}



void Display::set_pinout() {
	DDRB = 0x03;
	DDRA = 0xFF;
}
void Display::clear_display() {
	write_cmd(0x01, 0);
}

Display::Display(){
	set_pinout();
	init_display();
}

