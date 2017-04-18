#include "func.h"
#include <iomanip> 
#include "generador.h"
#include "cadena.h"
#include <sys/time.h>

using namespace std;
void experimento(CADENA cad);
double timeval_diff(struct timeval *a, struct timeval *b);

int main(int argc, const char* argv[]){
	
	if (argc != 4) {
		cout << "El numero de argumentos introducidos no es el correcto" << endl;
		cout << "Modo de funcionamiento: main cantidad_cadenas_generar caracter inicio_tam_cadena" << endl;
		cout << "la generacion de cadenas se iniciara en 10 y su incremento sera el doble del tamaño anterior" << endl;
		return -1;
	}
	
	int cant_cad = atoi(argv[1]);
	int tam_subcad = 0;
	char caracter = *argv[2];

	//tamaño de m 
	int a[] = {5, 10, 50, 100, 250, 500,1000};
	
	int ini = atoi(argv[3]);
	for (int i = 0; i < cant_cad; i++) {
		string str = generador(ini);
		CADENA cadena(str, tam_subcad, caracter);
		//cadena.print();
		cout << endl << "n: "<< cadena.getSize() << endl;

		for (int j = 0; j < 7 ; j++){
			if(a[j] <= cadena.getSize()){
				tam_subcad = a[j];
				cout << "m: " << tam_subcad<< endl;
				cadena.set_subcad(tam_subcad);
				experimento(cadena);
			}
				
		}
		
		//incrementamos el tamaño de la cadena
		ini = ini * 2;
	}
	return 0;
}
	
void experimento(CADENA cad) {

	struct timeval t_ini, t_fin;
  	double secs;
  	double resultado = 0.0;
	
	solucion res;
	for (int i = 0; i < 10; ++i){
		gettimeofday(&t_ini, NULL);   // Instante inicial
		res = dvd_subcad(cad, 0, cad.getSize()-1);
	    gettimeofday(&t_fin, NULL);  // Instante final

	    secs = timeval_diff( &t_ini, &t_fin);
	    resultado += secs;
	}
	resultado /=10;
	cout << resultado << endl;
}

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return  (b->tv_sec - a->tv_sec)*1000 + (b->tv_usec - a->tv_usec)/1000.0; 
}
