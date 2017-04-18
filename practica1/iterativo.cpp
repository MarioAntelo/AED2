#include "cadena.h"
#include "func.h"

using namespace std;


int main(int argc, const char* argv[]){
	
	if (argc != 4) {
		cout << "El numero de argumentos introducidos no es el correcto" << endl;
		cout << "Modo de funcionamiento: main cadena tamaño_subcadena caracter" << endl;
		return -1;
	}
	
	string str_cad = argv[1];
	int tam_subcad = atoi(argv[2]);
	char caracter = *argv[3];
	int apariciones = 0;
	int max = 0;
	int indice = 0;
	int i = 0;
	
	CADENA cadena(str_cad, tam_subcad, caracter);

	cadena.print();

	int n = cadena.getSize()-tam_subcad;
	for (i=0; i< n; i++){
		apariciones= cadena.comprobar_Subcad(i, i + tam_subcad);
		if(apariciones>max){
			max = apariciones;
			indice = i;
		}

	}

	cout << "solucion==> apariciones: "<< max << " empieza:" << indice << endl;
	return 0;
}
