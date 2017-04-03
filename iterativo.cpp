#include <iostream>
#include <fstream>
#include <string>
#include "cadena.h"

using namespace std;

string a, b; 
int m;
int main(int argc, char*argv[]){


	string txt;
	txt = argv[1];
	ifstream fichero;
	fichero.open (txt.c_str());
	int num_casos;
	fichero >> num_casos;
	for (int i = 0; i < num_casos; i++){
		fichero >> m; fichero >> a; fichero >> b;
		int posMax=-1;
		int valorMax=-1;
		int origen=0;
		int valorActual;
		while(origen+m <= a.length()){
			for (int j = 0; j < m; ++j ){
				valorActual+=abs(int(a[origen+j]) -int(b[origen+j]));
			}

			if (valorActual > valorMax){
				posMax=origen;
				valorMax=valorActual;
			}

			origen++;

		}
		cout << posMax << " " << valorMax << endl;
	}

}