#include "func.h"

using namespace std;

solucion dvd_subcad(CADENA cad, int inicio, int final){
	int caso_base, mitad;

	//caso base
	caso_base = cad.getSize_Subcad();
	if( tam_cad(inicio,final) <= caso_base){
		solucion s;
		s.max = cad.comprobar_Subcad(inicio, final);
		s.indice = inicio;
		s.final = final;
		return s;
	}
	else{
		int mitad = dividir(final);
		solucion s1,s2;
		s1 = dvd_subcad(cad, inicio, mitad);
		s2 = dvd_subcad(cad, mitad+1, final);
		return dvd_combinar(cad, s1, s2);
	}
}

/* metodo para el indice de la mitad
 * le pasamos el indice final y devuelve el de la mitad
*/
int dividir (int final){
	return (final/2) ;
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
		s3.max = s2.max;
		s3.indice = s2.indice;
		s3.final = s2.final;
	}else if (s1.max > s2.max){
		s3.max = s1.max;
		s3.indice = s1.indice;
		s3.final = s1.final;
	}

	//si hemos encontrado una cadena de apariciones no se recorre el centro de la cadena.
	if(s3.max < caso_base){
		m = caso_base -1;
		if(cad.comprobar_caracter(s1.final)
		{/*
			if(cad.comprobar_caracter(s2.inicio){
				//busco subcadena desde el final del nodo izquierdo
				//busco m-1 hacia la izquierda
				//busco m+1 hacia la derecha;
				for (int i = 1; i < m; ++i){
					if (cad.comprobar_caracter(indice))
				}
			}
			*/

		return s3;
	}
}
}