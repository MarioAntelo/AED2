#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

#define Max_alumnos 100

//VARIABLES GLOBALES//

struct pupitre{
	int alumno;
	int companero;
	
};

pupitre Solucion[Max_alumnos/2];

int alumnoSolo;  //ENTERO CONTENEDOR DE ALUMNOS NO SENTADOS
int numAlumnos;  //ENTERO CONTENEDOR DEL NÚMERO DE ALUMNOS

bool C[Max_alumnos];	//ARRAY CONTENEDOR DE POSIBLES ALUMNOS
int Companero[Max_alumnos];	//ARRAYA CONTENEDOR DEL COMPAÑERO DE CADA ALUMNO

int Amistad[Max_alumnos][Max_alumnos];	//MATRIZ CONTENEDORA DE LOS VALORES DE AMISTAD 
int Trabajo[Max_alumnos][Max_alumnos];	//MATRIZ CONTENEDORA DE LOS VALORES DE TRABAJO

int indiceSolucion;
int Beneficio;

//FUNCIONES//


//FUNCION INICIA VARIABLES//
void resetVariable(){
	alumnoSolo = 0;
	indiceSolucion = 0;
	Beneficio = 0;

	pupitre p;
	p.alumno = 0;
	p.companero = 0;
	for(int i = 0; i < Max_alumnos/2; i++){
		Solucion[i] = p;
	}

	for(int i = 0; i < Max_alumnos; i++){
		C[i] = 0;
		Companero[i] = -1;	//DISTINTO DE 0, YA QUE EL 0 REPRESENTA A UN COMPAÑERO
	}

	for(int i = 0; i < Max_alumnos; i++){
		for(int j = 0; j < Max_alumnos; j++){
			Amistad[i][j] = 0;
			Trabajo[i][j] = 0;
		}
	}
}


//METODO PARA INTRODUCIR VALORES DE LAS VARIABLES

void setVariable(int numAlumnos){

	alumnoSolo = numAlumnos;

	for(int i = 0; i < numAlumnos; i++){
		for(int j = 0; j < numAlumnos; j++){
			if (j == i){
				Amistad[i][j] = 0;			}
			else{
				int amistad = 0;
				cin >> amistad;
				Amistad[i][j] = amistad;
			}

		}
	}
	for(int i = 0; i < numAlumnos; i++){
		for(int j = 0; j < numAlumnos; j++){
			if (j == i){
				Trabajo[i][j] = 0;
			}
			else{
				int trabajo = 0;
				cin >> trabajo;
				Trabajo[i][j] = trabajo;
			}

		}
	}
}

int seleccionar(){
	int i = 0;
	for (i = 0; i < numAlumnos-1 && C[i] == true; i++){}
		if(i == numAlumnos-1 && C[i] == true)i = -1;

	return i;

}

void posible(int alumno){

	int mejorCompanero;
	int Beneficio = 0;
	int Max_beneficio = 0;

	int companero = seleccionar();
	mejorCompanero = companero;

	if(companero == -1){
			Companero[alumno] = -1;
	}	

	else{

			for(;companero < numAlumnos; companero++){

					if(C[companero] == true){}

					else{

							Beneficio = (Amistad[alumno][companero] + Amistad[companero][alumno])
													* (Trabajo[alumno][companero] + Trabajo[companero][alumno]);

							if (Beneficio >= Max_beneficio){

								mejorCompanero = companero;
								Max_beneficio = Beneficio;

							}
					}
			}
	}

		C[mejorCompanero] = true;

		pupitre p;
		p.alumno = alumno;
		p.companero = mejorCompanero;
		Solucion[indiceSolucion] = p;

		Beneficio += Max_beneficio;

		alumnoSolo--;

}

//////Falta imprimir la solución como lo pide el problema

void ImprimirSolucion(){

		bool elegidos[numAlumnos];
		int alumno;
		int companero;
		cout << Beneficio << endl;

		for(int i = 0; i < numAlumnos/2-1; i++){
			alumno = Solucion[i].alumno;
			companero = Solucion[i].companero;
			elegidos[alumno] = true;
            elegidos[companero] = true;
            cout << alumno << " " << companero << " ";     
     	}	     
     	alumno = Solucion[numAlumnos/2-1].alumno;
     	companero = Solucion[numAlumnos/2-1].companero;
     	elegidos[alumno] = true;
     	elegidos[companero] = true;
     
     	cout << alumno << " " << companero;
     	if(numAlumnos%2 != 0){
        	for(int i = 0; i < numAlumnos; i++){
            	if(elegidos[i]!= true){
                	cout << " " << i << endl;
                    break;                   
                }
                                   
			}              
		}
		else cout << endl;
}


void voraz(){
	while(alumnoSolo != 0 ){
		int alumno = seleccionar();

		C[alumno] = true;
		alumnoSolo--;

		posible(alumno);
		indiceSolucion++;
	}
	ImprimirSolucion();

}



int main(void){
	int numeroCasos;
	cin >> numeroCasos;
	while(numeroCasos > 0){

		resetVariable();
		cin >> numAlumnos;
		setVariable(numAlumnos);
		voraz();

		numeroCasos--;
	}

	return 0;
}