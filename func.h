#ifndef __FUNC
#define __FUNC

#include "cadena.h"
struct RES
{
	int max;
	int indice;
};

RES dvd_subcad(CADENA cad, int inicio, int final);
//RES dvd_combinar(CADENA cad, RES subcad1, RES subcad2);

#endif