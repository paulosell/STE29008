/*
 * gpio.cpp
 *
 *  Created on: 03/04/2019
 *      Author: aluno
 */

#include "gpio.h"
#include <avr/io.h>



GPIO::GPIO(int id, PortDirection_t dir){

	switch (id){
					case 2:
						_bit  = PE4;
						_PORT = &PORTE;
						_DDR  = &DDRE;
						_PIN  = &PINE;
						if(dir){
							DDRE |= (1 << _bit);
						} else {
							DDRE &= ~(1 << _bit);
						}
						break;
					case 3:
						_bit  = PE5;
						_PORT = &PORTE;
						_DDR  = &DDRE;
						_PIN  = &PINE;
						if(dir){
							DDRE |= (1 << _bit);
						} else {
							DDRE &= ~(1 << _bit);
						}
						break;
					case 4:
						_bit  = PG5;
						_PORT = &PORTG;
						_DDR  = &DDRG;
						_PIN  = &PING;
						if(dir){
							DDRG |= (1 << _bit);
						} else {
							DDRG &= ~(1 << _bit);
						}
						break;
					case 5:
						_bit  = PE3;
						_PORT = &PORTE;
						_DDR  = &DDRE;
						_PIN  = &PINE;
						if(dir){
							DDRE |= (1 << _bit);
						} else {
							DDRE &= ~(1 << _bit);
						}
						break;
					case 6:
						_bit  = PH3;
						_PORT = &PORTH;
						_DDR  = &DDRH;
						_PIN  = &PINH;
						if(dir){
							DDRH |= (1 << _bit);
						} else {
							DDRH &= ~(1 << _bit);
						}
						break;
					case 7:
						_bit  = PH4;
						_PORT = &PORTH;
						_DDR  = &DDRH;
						_PIN  = &PINH;
						if(dir){
							DDRH |= (1 << _bit);
						} else {
							DDRH &= ~(1 << _bit);
						}
						break;
					case 8:
						_bit  = PH5;
						_PORT = &PORTH;
						_DDR  = &DDRH;
						_PIN  = &PINH;
						if(dir){
							DDRH |= (1 << _bit);
						} else {
							DDRH &= ~(1 << _bit);
						}
						break;
					case 9:
						_bit  = PH6;
						_PORT = &PORTH;
						_DDR  = &DDRH;
						_PIN  = &PINH;
						if(dir){
							DDRH |= (1 << _bit);
						} else {
							DDRH &= ~(1 << _bit);
						}
						break;


	}


}
GPIO::~GPIO(){}

bool GPIO::read(){
	return (* _PIN & (1 << _bit));

}

void GPIO::write(bool val){
	if (val == false){
		 * _PORT &= ~(1 << _bit);
	} else {
		 * _PORT |= (1 << _bit);
	}
}

void GPIO::toggle(){
	* _PORT ^= (1 << _bit);

}
