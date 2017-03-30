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
		cout << inicio << "--" << final<<"--" <<s.max<< endl;
		return s;
	}
	else{
		int mitad = dividir(final);
		solucion s1,s2;
		s1 = dvd_subcad(cad, inicio, mitad);
		cout << s1.max <<"--"<< s1.indice<<"--"<< endl;
		s2 = dvd_subcad(cad, mitad+1, final);
		cout << s2.max << s2.indice << endl;
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
	if (s1.max <= s2.max){
		s3.max = s2.max;
		s3.indice = s2.indice;
	}else if (s1.max > s2.max){
		s3.max = s1.max;
		s3.indice = s1.indice;
	}
	return s3;
}