/*
 * fila.h
 *
 *  Created on: 18 de mai de 2019
 *      Author: paulosell



#ifndef FILA_H_
#define FILA_H_
#include <stdio.h>
template <typename T> class Fila{
public:

	Fila (uint8_t capacidade);
	void enfileira (const T  data);
	T desenfileira();
	bool vazia();
	bool cheia();
	uint8_t comprimento();
	uint8_t capacidade();

private:
	uint8_t _capacidade;
	uint8_t _quantidade;
	T * _buffer;
	uint8_t _inicio;
	uint8_t _final;

};



#endif  FILA_H_ */

#ifndef FILA_H_
#define FILA_H_

template <typename T, int capacidade> class Fila {

public:
	Fila() {
		_inicio = 0;
		_final = 0;
		_quantidade = 0;
	}

	void push(T data){

		_buffer[_final] = data;
		_final  = _final + 1;
		_quantidade = _quantidade + 1;
		 if (_final == capacidade) _final = 0;

	}

	T pop(){
			T data = _buffer[_inicio];
			_quantidade = _quantidade - 1;
			_inicio = _inicio + 1;
			if (_inicio == capacidade) _inicio = 0;
			return data;
	}

	int get_size(){
		return _quantidade;
	}

	bool cheia(){
		return (_quantidade == capacidade);
	}
	bool vazia(){
		return(_quantidade == 0);
	}
private:
	T _buffer[capacidade];
	int _inicio;
	int _final;
	int _quantidade;
};

#endif /* FILA_H_ */
