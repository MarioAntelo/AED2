#ifndef __CADENA
#define __CADENA

#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;
class CADENA {
	private:
		std::vector<char> cad;
		int size;
		int size_subcad;
		char caracter;

	public:
		//Constructores
		CADENA(){ size = 0;};
		CADENA(std::string str, int subcad_size, char caracter);
		//Metodos sobre el array
		std::vector<char> getCad() { return cad; };
		void push_back(char c);
		void clear();
		//Metodos sobre size
		int getSize() { return size; };
		//Metodos de debug
		void print();

		//metodo para la subcadena
		int getSize_Subcad(){return size_subcad;};
		char getCaracter(){return caracter;};

		//metodo comprueba la apariciones del caracter
		int comprobar_Subcad(int inicio, int final);
		bool comprobar_caracter(int indice);

};

#endif