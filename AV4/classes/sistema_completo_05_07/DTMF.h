/*
 * DTMF.h
 *
 *  Created on: 25 de jun de 2019
 *      Author: paulosell
 */

#ifndef DTMF_H_
#define DTMF_H_
#include "GPIO.h"

class DTMF{
public:
	enum DTMF_t{
		DIGITO_0 		 = 0,
		DIGITO_1 		 = 1,
		DIGITO_2 		 = 2,
		DIGITO_3 		 = 3,
		DIGITO_4		 = 4,
		DIGITO_5		 = 5,
		DIGITO_6 		 = 6,
		DIGITO_7 		 = 7,
		DIGITO_8		 = 8,
		DIGITO_9 		 = 9,
		DIGITO_asterisco = 10,
		DIGITO_cerca	 = 11

	};
	DTMF(GPIO * c1, GPIO * c2, GPIO * c3, GPIO * c4, GPIO *l1,
			GPIO * l2, GPIO * l3, GPIO * l4);
	~DTMF(){};
	void send_dtmf(uint8_t digito);

private:
	GPIO * colunas[4];
	GPIO * linhas[4];
};




#endif /* DTMF_H_ */
