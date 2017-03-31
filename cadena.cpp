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
/*
 * Metodo almacena un caracter en el array
 * recibe un caracter
*/
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
 * Metodo que comprueba las apariciones de un Caracter
 * Recibe: indices de la inicio y final de la subcadena a tratar
 * devuelve el max de apariciones concecutivas del caracter.
 */
int CADENA::comprobar_Subcad(int inicio, int final){
	int i, max, aux;
	i = inicio;
	max=0;
	aux =0;
	for (; i <= final ; i++){
		if (comprobar_caracter(cad[i]))
			aux++;
		else
			aux=0;

		if(aux >= max)
				max = aux;
	}
	return max;
}

/*
 * Metodo que comprueba si es el caracter buscado
 * Recibe: indices de la inicio y final de la subcadena a tratar
 * devuelve el max de apariciones concecutivas del caracter.
 */
bool CADENA::comprobar_caracter(int indice){
		if (cad[indice] == caracter)
			return true;
		else
			return false;
}