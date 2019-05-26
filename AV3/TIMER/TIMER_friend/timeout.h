/*
 * timeout.h
 *
 *  Created on: 03/05/2019
 *      Author: aluno
 */

#ifndef TIMEOUT_H_
#define TIMEOUT_H_
#include <stdio.h>
typedef void (*CALLBACK_t)(void);
class Timeout{
	friend class Timer;
public:
	Timeout(){};
	Timeout(uint32_t interval, CALLBACK_t callback);
	void setTimeout(uint32_t interval, CALLBACK_t callback);
	void checkTimeout();
	void callback(){(*_pCAllback)();}
	bool isEnabled();
	void enableTimeout();
	void disableTimeout();
	bool hasEvent();
	void disableEvent();

private:
	bool _event;
	bool _enable;
	CALLBACK_t _pCAllback;
	uint32_t _counter;
	uint32_t _interval;

};




#endif /* TIMEOUT_H_ */
