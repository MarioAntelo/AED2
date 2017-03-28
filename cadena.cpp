#include "cadena.h"

using namespace std;

/*prueba*/


/**
 * Método de construcción de la cadena a recorrer.
 * Recibe un string que recorrerá carácter
 * a carácter para ir construyendo un vector de caracteres que representara a la cadena.
 * recibe el tamaño de la subcadena a buscar
 * recibe el caracter que buscaremos en la subcadena
 */
CADENA::CADENA(string str, int size_sub, char c){
	// Inizializa variables auxiliares
	size = 0;
	size_subcad = size_sub;
	caracter = c;

	std::string::iterator it = str.begin();
	
	for(; it != str.end(); ++it) {
		// Recorremos caracter a caracter 
		cad.push_back(*it);
		size++;
	}
}

void CADENA::push_back(char c) { 
	cad.push_back(c);
	size++;
}

void CADENA::clear() { 
	cad.clear(); 
	size = 0;
}

/**
 * Método que imprime la cadena tratada.
 **/
void CADENA::print(){
	std::vector<char>::iterator it = cad.begin();
	for (; it != cad.end(); it++)
		cout << *it;
	cout << endl;
}

/*
 * Metodo que dado un indice comprueba
 * cuantas veces aparece el caracter dentro una
 * subcadena de tamaño m.
 * devuelve el tamaño.
 */
int CADENA::comprobar_Subcad(int indice){
	int i, tam, max;
	i = indice;
	max=0;
	tam = indice+ size_subcad;
	for (; i < tam ; i++){
		if (cad[i] == caracter){
			max++;	
		}
	}
	return max;
}
