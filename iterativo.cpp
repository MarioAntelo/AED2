#include <iostream>
#include <fstream>
#include <string>
#include "cadena.h"

using namespace std;

struct solucion{
	int inicio;
	int final;
};

bool isCaracter(char c){
	if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' 
		|| c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' 
		|| c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' 
		|| c == 'y' || c == 'z' ) return true;
     return false;
}


solucion dvdIter(char* caracter){
	solucion s;
	s.inicio = 0;
	s.final = 0;
	int origenSubcadena=0;
	int finalSubcadena=0;

}