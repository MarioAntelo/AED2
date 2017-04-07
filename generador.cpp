/*Generador de Prueba
Tamaño de la cadena N
Tamaño de la subcadena m
Carácter buscado c
*/
#include "generador.h"

/* metodo genRandom
 * busca un caracter aleatorio
*/
char genRandom(){
	return alfabeto[rand() % stringLength];
}

/* metodo generador
 * genera cadenas de tamaño n
 * Devuelve la cadena generada
*/
string generador(int size){
	std::string Str;
	for(unsigned int i = 0; i < size; ++i){
		Str += genRandom();
    }
    return Str;
}
