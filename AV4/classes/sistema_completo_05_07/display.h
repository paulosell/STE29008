
#ifndef DISPLAY_H_
#define DISPLAY_H_


class Display{
public:
	Display();
	~Display(){};
	void escreve_LCD(uint8_t c);
	void clear_display();
	void quebra_linha();
private:
	void init_display();
	void write_cmd(unsigned char c, char cd);
	void pulso_enable();
	void set_pinout();
};


#endif /* DISPLAY_H_ */

