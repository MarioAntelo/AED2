#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


class Avion
{
	private:
		int beneficio;
		int tiempo;
	public:
		Avion(){
			beneficio = 0;
			tiempo = 0;
		};

		int getBeneficio()const {return beneficio;};
		int getTiempo(){return tiempo;};
		void setBeneficio(int b){beneficio = b;};
		void setTiempo(int t){tiempo=t;};

		void show(){
			cout <<"--"<< tiempo << " "<< beneficio << endl;
		};

		bool operator<(const Avion &A) const {
			return beneficio > A.getBeneficio();
		}
};


/*
* Función seleccionar
* devuelve un candidato y lo quita de la lista
*/
Avion seleccionar(vector<Avion> &C){
	Avion x = C.front();
	C.erase(C.begin());
	return x;
}

/*
* Función solucion
*comprueba si un conjunto de candidatos es una solucion
*los candidatos seran una solucion si la cantidad de candidatos
*es igual a la cantidad de horas en la que se puede aterrizar
*/
bool solucion(int Aterriza, int horario){
	if (Aterriza == horario)
		return true;
	return false;

}

/*
* Función factible
* indica si a partir del conjunto S y añadiendo x
* es posible construir una solucion
*/
bool factible(int Aterriza, int horario){
	if (Aterriza <= horario)
		return true;
	return false;
}

/*
* Función insertar
* inserta un elemento a la solucion
*posiblemente construir un tipo solucion
*tipo solucion lista con entero que lleve el coste de la solucion
*/
void insertar(vector<Avion> &S, Avion X, int *pista){
	//tiempo maximo que aguanta el avion en el aire
	int i = X.getTiempo();
	int size = S.size();
	if(i > size)
		i = size;
	i--;

	for (; i>=0 ;i--){
		if(S[i].getBeneficio() < X.getBeneficio())
		{
			S[i] = X;
			pista++;
			i=-1;
		}
	}
}


/*
*Algoritmo Voraz
*recibe:
	horario-> es la unidad maxima de aviones que podran aterrizar
	A -> la cantidad de aviones que esperan orden de aterrizaje
	C -> todos los posibles aviones 
*/
void aterrizaje(int horario , vector<Avion> &C, vector<Avion> &S){
	//ordenamos los candidatos en funcion del beneficio
	sort(C.begin(), C.end());

	//indica cuantos aviones van a aterrizar
	int aterriza=0;
	Avion x;
	//seleccionar ya quita al candidato de la lista
	while(C.size() != 0 && (solucion(aterriza, horario)==false)) {	
		x = seleccionar(C);
		if (factible(aterriza, horario)){
			insertar(S, x, &aterriza);
		}

	}
}

/*
*Función Objetivo
*dada una solucion devuelve el coste
*asociada a la misma
*/
//int objetivo(list<int> S){}

int main (void)
{
    int casos, Ut, A;
    cin >> casos;
    
    for (int i = 0; i < casos; ++i){
        cin >> Ut;
        cin >> A;

		
        //creo el array que contendra los aviones
        vector<Avion> aviones;
        vector<Avion> Solucion;
        Avion x;
        Solucion.assign(Ut, x);
        aviones.assign(A, x);
        
        int aux;
        //inserto los tiempo de los aviones
        for (int j = 0; j < A; ++j){
            cin >> aux;
            aviones[j].setTiempo(aux);
        }
    	
    	//inserto el beneficio que cada avion reporta
        for (int j = 0; j < A; ++j){
            cin >> aux;
            aviones[j].setBeneficio(aux);
        }

        //ejecuto el algoritmo voraz
        aterrizaje(Ut, aviones, Solucion);
        
        
		int bene = 0;
        for(int j=0; j<Ut ; j++)
        	bene = bene+Solucion[j].getBeneficio();
        cout << bene << endl;
        //borramos la estructura de los aviones

    }
 
}
