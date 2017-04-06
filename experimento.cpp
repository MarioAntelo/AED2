#include "func.h"
#include <iomanip> 
#include "generador.h"
#include "cadena.h"

using namespace std;
void experimento(CADENA cad);


int main(int argc, const char* argv[]){
	
	if (argc != 3) {
		cout << "El numero de argumentos introducidos no es el correcto" << endl;
		cout << "Modo de funcionamiento: main cantidad_cadenas_generar caracter" << endl;
		cout << "la generacion de cadenas se iniciara en 10 y su incremento sera el doble del tamaño anterior" << endl;
		return -1;
	}
	
	int cant_cad = atoi(argv[1]);
	int tam_subcad = 0;
	char caracter = *argv[2];
	
	int ini = 1000;
	for (int i = 0; i <= cant_cad; i++) {
		string str = generador(ini);
		CADENA cadena(str, tam_subcad, caracter);
		cadena.print();
		cout << "tam: "<< cadena.getSize() << endl;

		//se hace el experimento con  4 tamaño de m
		double porcentaje = 1;
		for (int j = 0; j < 4 ; j++){
			tam_subcad = cadena.getSize() * porcentaje;
			cout << "tamano m: " << tam_subcad<< endl;
			cadena.set_subcad(tam_subcad);
			experimento(cadena);
			porcentaje /= 2; 
				
		}
		
		//incrementamos el tamaño de la cadena
		ini = ini * 2;
	}
	return 0;
}
	
void experimento(CADENA cad) {

	clock_t start;
	time_t now;
	
	
	solucion res;
	for (int i = 0; i < 10; ++i){
		start = clock();
		now = time(NULL);
		
		res = dvd_subcad(cad, 0, cad.getSize()-1);
		cout << "DyV Time: " <<(clock() - start) / (double)(CLOCKS_PER_SEC) << " ms" << endl;
	}
	

	cout << "solucion==> apariciones: "<< res.max;
	cout<< " empieza:" << res.ini_subcad << endl;
}
