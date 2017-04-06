/*Generador de Prueba
Tamaño de la cadena N
Tamaño de la subcadena m
Carácter buscado c
*/
#include "generador.h"

char genRandom(){
	return alfabeto[rand() % stringLength];
}

string generador(int size){
	std::string Str;
	for(unsigned int i = 0; i < size; ++i){
		Str += genRandom();
    }
    return Str;
}
