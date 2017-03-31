#include "func.h"

using namespace std;

solucion dvd_subcad(CADENA cad, int inicio, int final){
	int caso_base, mitad;

	//caso base
	caso_base = cad.getSize_Subcad();
	int tam = tam_cad(inicio,final);
	cout << "tam: "<<tam << "---" << caso_base <<"--- i:" << inicio<<" f:"<< final<< endl;
	if( tam <= caso_base){
		solucion s;
		s.max = cad.comprobar_Subcad(inicio, final);
		s.inicio = inicio;
		s.final = final;
		return s;
	}
	else{
		int mitad = dividir(inicio,final);
		solucion s1,s2;
		s1 = dvd_subcad(cad, inicio, mitad);
		s2 = dvd_subcad(cad, mitad+1, final);
		return dvd_combinar(cad, s1, s2);
	}
}

/* metodo para el indice de la mitad
 * le pasamos el indice final y devuelve el de la mitad
*/
int dividir (int inicio, int final){
	int aux =0;
	aux = (final-inicio)/2;
	aux = aux + inicio;
	return aux;
}

/**
 * Metodo para saber la cantidad de caracteres entre 2 indices.
**/
int tam_cad(int inicio, int final){
	return (final - inicio) + 1;
}

solucion dvd_combinar(CADENA cad, solucion s1, solucion s2){

	solucion s3;
	int caso_base = cad.getSize_Subcad();
	if (s1.max <= s2.max){
		cout << "der"<<endl;
		s3.max = s2.max;
		s3.inicio = s2.inicio;
		s3.final = s2.final;
		/*if(s3.max < caso_base){
			s3.inicio = s2.final - (caso_base-1);
			s3.final = s2.final;
		}else{
			s3.inicio = s2.inicio;
			s3.final = s2.final;
		}*/
	}else if (s1.max > s2.max){
		cout << "izq"<<endl;
		s3.max = s1.max;/*
		if(s3.max < caso_base){
			s3.inicio = s1.final - (caso_base-1);
			s3.final = s1.final;
		}else{*/
			s3.inicio = s1.inicio;
			s3.final = s1.final;
		//}
	}
	cout << "max: " << s3.max << " i:"<< s3.inicio << " f:"<< s3.final <<endl;

	//si hemos encontrado una cadena de apariciones no se recorre el centro de la cadena.
	if(s3.max < caso_base){
		int aux =0;
		int indice =0;
		int m = caso_base -1;
		cout << "f: " <<s1.final<<endl;
		if(cad.comprobar_caracter(s1.final)){
			aux++;
			
			if(cad.comprobar_caracter(s2.inicio)){
				//busco subcadena desde el final del nodo izquierdo
				//busco m-1 hacia la izquierda
				//busco m+1 hacia la derecha;
				for (int i = 1; (i < m) && (aux <=caso_base) ; ++i){
					if (cad.comprobar_caracter(s1.final-i)){
						aux++;
						indice= s1.final-i;
					}
					if (cad.comprobar_caracter(s2.inicio+i))
						aux++;
				}
				cout << "entra " << aux << "-";
				if(aux >= s3.max){
					
					s3.max = aux;
					s3.inicio = indice;
					//s3.final = indice + aux;
				}
			}

		}
	}
	return s3;
}	
