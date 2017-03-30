#ifndef __FUNC
#define __FUNC

#include "cadena.h"
typedef struct {
	int max;
	int indice;
}solucion;

solucion dvd_subcad(CADENA , int, int );
solucion dvd_combinar(CADENA , solucion, solucion);

//metodos auxiliares
int dividir(int);
int tam_cad(int,int);

#endif