#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "DTMF.h"
#include "uart.h"
#include "Teclado.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "EEPROM.h"


//	================================== //
//		   DECLARAÇÃO DO DTMF 		   //
//  ================================== //

GPIO c2(23 , GPIO::OUTPUT);
GPIO c3(25 , GPIO::OUTPUT);
GPIO c4(27 , GPIO::OUTPUT);
GPIO c1(29 , GPIO::OUTPUT);

GPIO l3(22 , GPIO::OUTPUT);
GPIO l2(24 , GPIO::OUTPUT);
GPIO l1(26 , GPIO::OUTPUT);
GPIO l4(28 , GPIO::OUTPUT);

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

UART serial((uint32_t) 9600, UART::DATABITS_8, UART::NONE, UART::STOPBIT_1, UART::ON, UART::UART0);


//	================================== //
//		  DECLARAÇÃO DA EEPROM     	   //
//  ================================== //

EEPROM  e;


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
const unsigned char inicio[] PROGMEM = "Bem vindo!\n";
const unsigned char MenuPrincipalOpcaoA[] PROGMEM = "Digite A para tocar sequencia\n";
	const unsigned char MenuOpcaoAPrincipal[] PROGMEM  = "Selecione a sequencia\n";
	const unsigned char MenuOpcaoAOpcao1[] PROGMEM = "Pressione 1 para primeira sequencia\n";
	const unsigned char MenuOpcaoAOpcao2[] PROGMEM = "Pressione 2 para segunda sequencia\n";
	const unsigned char MenuOpcaoAOpcao3[] PROGMEM = "Pressione 3 para terceira sequencia\n";
const unsigned char MenuPrincipalOpcaoB[] PROGMEM = "Digite B para gravar sequencia\n";
	const unsigned char MenuOpcaoBPrincipal[] PROGMEM = "Selecione a posição\n";
	const unsigned char MenuOpcaoBOpcao1[] PROGMEM = "1 para gravar na primeira posição\n";
	const unsigned char MenuOpcaoBOpcao2[] PROGMEM = "2 para gravar na segunda posição\n";
	const unsigned char MenuOpcaoBSair[] PROGMEM = "Pressione D para voltar\n";
	const unsigned char MenuOpcaoBGravar[] PROGMEM = "Pressione A para gravar\n";
	const unsigned char MenuOpcaoBDigite[] PROGMEM = "Digite a sequencia\n";
const unsigned char MenuPrincipalOpcaoC[] PROGMEM = "Digite C para o modo online\n";
	const unsigned char MenuOpcaoCIn[] PROGMEM = "Modo online ativado\n";
	const unsigned char MenuOpcaoCOut[] PROGMEM = "Saindo do modo online\n";

uint8_t * pos_inicio = 0;
uint8_t dado = 0;


int main(void){
	sei();
	on.set(true);
	stop.set(false);
	for(unsigned int i = 0; i < sizeof(inicio); i++){
		serial.put(pgm_read_byte(&inicio[i]));
	}


	while(true){
		serial.put('\n');
		for(unsigned int i = 0; i < sizeof(MenuPrincipalOpcaoA); i++){
			serial.put(pgm_read_byte(&MenuPrincipalOpcaoA[i]));
		}
		for(unsigned int i = 0; i < sizeof(MenuPrincipalOpcaoB); i++){
			serial.put(pgm_read_byte(&MenuPrincipalOpcaoB[i]));
		}
		for(unsigned int i = 0; i < sizeof(MenuPrincipalOpcaoC); i++){
			serial.put(pgm_read_byte(&MenuPrincipalOpcaoC[i]));
		}

		while(t.varredura());
		uint8_t tecla = t.getTecla();

		if (tecla == 20){
			for(unsigned int i = 0; i < sizeof(opcao); i++){
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			tocar_sequencia();
		}

		if(tecla == 21){
			for(unsigned int i = 0; i < sizeof(opcao); i++){
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			gravar_sequencia();
		}

		if(tecla == 22){
			for(unsigned int i = 0; i < sizeof(opcao); i++){
				serial.put(pgm_read_byte(&opcao[i]));
			}
			serial.put(tecla);
			serial.put('\n');
			online();
		}
	}

}

void tocar_sequencia(){
	for(unsigned int i = 0; i < sizeof(MenuOpcaoAPrincipal); i++){
		serial.put(pgm_read_byte(&MenuOpcaoAPrincipal[i]));
	}

	for(unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao1); i++){
		serial.put(pgm_read_byte(&MenuOpcaoAOpcao1[i]));
	}

	if (e.read(pos_inicio) == 1 && e.read(pos_inicio+1) == 1){
		for(unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao2); i++){
			serial.put(pgm_read_byte(&MenuOpcaoAOpcao2[i]));
		}

		for(unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao3); i++){
			serial.put(pgm_read_byte(&MenuOpcaoAOpcao3[i]));
		}

		while(t.varredura());
		uint8_t tecla = t.getTecla();
		if(tecla == 1){
			uint8_t digitos[sizeof(seq1)];
			serial.put(0x31);
			for(unsigned int i = 0; i < sizeof(seq1); i++){
				digitos[i] =  pgm_read_byte(&seq1[i]);

			}
			on.toggle();
			stop.toggle();
			for(unsigned int i = 0; i < sizeof(digitos); i ++){
				serial.put(digitos[i]);
				d.send_dtmf(digitos[i]-0x30);
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 2){
			on.toggle();
			stop.toggle();
			for(int i = 0; i < 10; i++){
				serial.put(e.read(i+pos_inicio+20));
				d.send_dtmf(e.read(i+pos_inicio+20));
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if (tecla == 3){
			on.toggle();
			stop.toggle();
			for(int i = 0; i < 10; i++){
				serial.put(e.read(i+pos_inicio+40));
				d.send_dtmf(e.read(i+pos_inicio+40));
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 23){
			return;

		}

	} else if (e.read(pos_inicio)==1){

		for(unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao2); i++){
			serial.put(pgm_read_byte(&MenuOpcaoAOpcao2[i]));
		}


		while(t.varredura());
		uint8_t tecla = t.getTecla();
		if(tecla == 1){
			uint8_t digitos[sizeof(seq1)];
			serial.put(0x31);
			for(unsigned int i = 0; i < sizeof(seq1); i++){
				digitos[i] =  pgm_read_byte(&seq1[i]);

			}
			on.toggle();
			stop.toggle();
			for(unsigned int i = 0; i < sizeof(digitos); i ++){
				serial.put(digitos[i]);
				d.send_dtmf(digitos[i]-0x30);
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 2){
			on.toggle();
			stop.toggle();
			for(int i = 0; i < 10; i++){
				serial.put(e.read(i+pos_inicio+20));
				d.send_dtmf(e.read(i+pos_inicio+20));
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 23){
			return;

		}

	} else if (e.read(pos_inicio+1)==1){

		for(unsigned int i = 0; i < sizeof(MenuOpcaoAOpcao3); i++){
			serial.put(pgm_read_byte(&MenuOpcaoAOpcao3[i]));
		}


		while(t.varredura());
		uint8_t tecla = t.getTecla();
		if(tecla == 1){
			uint8_t digitos[sizeof(seq1)];
			serial.put(0x31);
			for(unsigned int i = 0; i < sizeof(seq1); i++){
				digitos[i] =  pgm_read_byte(&seq1[i]);

			}
			on.toggle();
			stop.toggle();
			for(unsigned int i = 0; i < sizeof(digitos); i ++){
				serial.put(digitos[i]);
				d.send_dtmf(digitos[i]-0x30);
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 3){
			on.toggle();
			stop.toggle();
			for(int i = 0; i < 10; i++){
				serial.put(e.read(i+pos_inicio+20));
				d.send_dtmf(e.read(i+pos_inicio+20));
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}

		if(tecla == 23){
			return;

		}

	} else {

		while(t.varredura());
		uint8_t tecla = t.getTecla();
		if(tecla == 1){
			uint8_t digitos[sizeof(seq1)];
			serial.put(0x31);
			for(unsigned int i = 0; i < sizeof(seq1); i++){
				digitos[i] =  pgm_read_byte(&seq1[i]);

			}
			on.toggle();
			stop.toggle();
			for(unsigned int i = 0; i < sizeof(digitos); i ++){
				serial.put(digitos[i]);
				d.send_dtmf(digitos[i]-0x30);
				_delay_ms(1000);
			}
			on.toggle();
			stop.toggle();
			return;
		}



		if(tecla == 23){
			return;

		}

	}

}

void online(){
	for(unsigned int i = 0; i < sizeof(MenuOpcaoCIn); i++){
		serial.put(pgm_read_byte(&MenuOpcaoCIn[i]));
	}

	bool flag = false;
	on.toggle();
	stop.toggle();
	while(!flag){
		while(t.varredura());
		uint8_t tecla = t.getTecla();
		if (tecla == 1 || tecla == 2 || tecla == 3 || tecla == 4 || tecla == 5 || tecla == 6
				|| tecla == 7 || tecla == 8 || tecla == 9){
			d.send_dtmf(tecla);
		} else if (tecla == 23){
			flag = true;
		}

	}
	on.toggle();
	stop.toggle();
	for(unsigned int i = 0; i < sizeof(MenuOpcaoCOut); i++){
		serial.put(pgm_read_byte(&MenuOpcaoCOut[i]));
	}


}

void gravar_sequencia(){
	bool flag = true;
	while(flag){
		for(unsigned int i = 0; i < sizeof(MenuOpcaoBOpcao1); i++){
			serial.put(pgm_read_byte(&MenuOpcaoBOpcao1[i]));
		}

		for(unsigned int i = 0; i < sizeof(MenuOpcaoBOpcao2); i++){
			serial.put(pgm_read_byte(&MenuOpcaoBOpcao2[i]));
		}
		for(unsigned int i = 0; i < sizeof(MenuOpcaoBSair); i++){
			serial.put(pgm_read_byte(&MenuOpcaoBSair[i]));
		}

		while(t.varredura());
		uint8_t pos = t.getTecla();

		if (pos == 1 || pos == 2){
			for(unsigned int i = 0; i < sizeof(MenuOpcaoBDigite); i++){
				serial.put(pgm_read_byte(&MenuOpcaoBDigite[i]));
			}

			Fila<uint8_t, 10> digitos;
			while (!digitos.cheia()){
				while(t.varredura());
				uint8_t tecla = t.getTecla();
				serial.put(tecla+0x30);
				if ((tecla == 1 || tecla == 2 || tecla == 3 || tecla == 4 || tecla == 5 || tecla == 6
						|| tecla == 7 || tecla == 8 || tecla == 9)){
					digitos.push(tecla);
				}

			}

			for(unsigned int i = 0; i < sizeof(MenuOpcaoBGravar); i++){
				serial.put(pgm_read_byte(&MenuOpcaoBGravar[i]));
			}

			for(unsigned int i = 0; i < sizeof(MenuOpcaoBSair); i++){
				serial.put(pgm_read_byte(&MenuOpcaoBSair[i]));
			}

			while(t.varredura());
			uint8_t tecla = t.getTecla();
			if(tecla == 20){
				if (pos == 1){
					on.toggle();
					stop.toggle();
					e.write_burst(pos_inicio+20, digitos);
					e.write(pos_inicio,1);
					on.toggle();
					stop.toggle();
				}
				if (pos == 2){
					on.toggle();
					stop.toggle();
					e.write_burst(pos_inicio+40, digitos);
					e.write(pos_inicio+1,1);
					on.toggle();
					stop.toggle();
				}
			} else if (tecla == 23){
				break;
			}
		}


		if (pos ==  23){
			flag = false;
		}

	}

};

