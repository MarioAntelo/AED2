#ifndef __FUNC
#define __FUNC

#include "cadena.h"
typedef struct {
	int max;
	int inicio;
	int final
}solucion;

solucion dvd_subcad(CADENA , int, int );
solucion dvd_combinar(CADENA , solucion, solucion);

//metodos auxiliares
int dividir(int);
int tam_cad(int,int);

#endif