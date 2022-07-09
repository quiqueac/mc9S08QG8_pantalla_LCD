#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void mcuinit(void);
void enable(void);
void comando(unsigned char x);
void datos(unsigned char x);
void inicializar(unsigned char *p);
void cadena(unsigned char *p);
void retardo(void);

void main(void) {
	unsigned char tabla[8] = {0x38, 0x38, 0x38, 0x38, 0x0f, 0x06, 0x01, 0x00};
	unsigned char mensaje[11] = {"HOLA MUNDO"};
	SOPT1 = 0x12;
	mcuinit();
	inicializar(&tabla[0]);
	cadena(&mensaje[0]);
	comando(0xC0);
	//dato('7');
	//dato('K');
	fin:
	goto fin;
}

void mcuinit(void) {
	PTBDD = 0xFF;
	PTADD_PTADD0 = 1;
	PTADD_PTADD1 = 1;
	PTBD = 0x38;
	PTAD_PTAD0 = 0; // RS = 0
	PTAD_PTAD1 = 0; // E = 0
}

void enable(void) {
	PTAD_PTAD1 = 1;
	retardo();
	PTAD_PTAD1 = 0;
}

void comando(unsigned char x) {
	PTBD = x;
	PTAD_PTAD0 = 0;
	enable();
}

void datos(unsigned char x) {
	PTBD = x;
	PTAD_PTAD0 = 1;
	enable();
}

void inicializar(unsigned char *p) {
	while(*p != 0x00) {
		comando(*p);
		p++;
	}
}

void cadena(unsigned char *p) {
	while(*p != 0x00) {
		datos(*p);
		p++;
	}
}

void retardo(void) {
	unsigned int x = 0xFFF;
	while(x != 0) {
		x--;
	}
}
