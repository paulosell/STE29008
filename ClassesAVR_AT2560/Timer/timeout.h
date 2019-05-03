/*
 * timeout.h
 *
 *  Created on: 03/05/2019
 *      Author: aluno
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_

typedef void (*CALLBACK_t)(void);
class Timeout{
public:

	Timeout();
	void config(uint32_t interval, CALLBACK_t callback);
	void checkTimeout();
	void callback(){(*_pCAllback)();}
	bool isEnabled();
	bool hasEvent();

private:
	bool _event;
	bool _enable;
	CALLBACK_t _pCAllback;
	uint32_t _counter;
	uint32_t _interval;

};




#endif /* TIMEOUT_H_ */
