#include "func.h"

using namespace std;

solucion dvd_subcad(CADENA cad, int inicio, int final){
	int caso_base, mitad;

	//caso base
	caso_base = cad.getSize_Subcad();
	int tam = tam_cad(inicio,final);
	if( tam <= caso_base){
		solucion s;
		s.max = cad.comprobar_Subcad(inicio, final);
		s.inicio = inicio;
		s.final = final;
		s.ini_subcad= inicio;
		return s;
	}
	else{
		int mitad = dividir(inicio,final);
		solucion s1,s2, s3;
		s1 = dvd_subcad(cad, inicio, mitad);
		s2 = dvd_subcad(cad, mitad+1, final);
		//cout << s1.max <<"-" << s1.inicio<<"-" << s1.final<<"--" << s1.ini_subcad<< endl; 
		//cout << s2.max <<"-" << s2.inicio<<"-" << s2.final<<"--" << s2.ini_subcad <<endl;
		s3 = dvd_combinar(cad, s1, s2);

		//cout << s3.max <<"-" << s3.inicio<<"-" << s3.final<<"--" << s3.ini_subcad<< endl;
		return s3;
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
	if (s1.max < s2.max){
		s3.max = s2.max;
		
		if(tam_cad(s2.inicio, s2.final) <= caso_base){
			s3.ini_subcad = s2.inicio;
		}else if(caso_base >= s2.max)
			s3.ini_subcad = s2.ini_subcad;
	}else if (s1.max >= s2.max){
		s3.max = s1.max;

		if(tam_cad(s1.inicio, s1.final) <= caso_base){
			s3.ini_subcad = s1.inicio;
		}else if(s1.max >= s2.max)
			s3.ini_subcad = s1.ini_subcad;
	}
	//modifico los punteros de la subcadena.
	s3.inicio = s1.inicio;
	s3.final = s2.final;

	//si hemos encontrado una cadena de apariciones no se recorre el centro de la cadena.
	if(s3.max < caso_base){
		int aux =0;
		int indice =0;
		bool var = true;
		if(cad.comprobar_caracter(s1.final)){
			aux++;
			if(cad.comprobar_caracter(s2.inicio)){
				//busco subcadena desde el final del nodo izquierdo
				//busco m-1 hacia la izquierda
				//busco m+1 hacia la derecha;
				indice = s1.final;
				for (int i = 1; (i < caso_base) && (aux < caso_base) ; ++i){
					if(var){
						if (cad.comprobar_caracter(s1.final-i)){
							aux++;
							indice= s1.final-i;
						}else
							var = false;
					}
					if (cad.comprobar_caracter(s1.final+i))
						aux++;
				}
				
				if(aux > s3.max){
					s3.max = aux;
					s3.ini_subcad = indice;
				}
			}

		}
	}
	return s3;
}	
