#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;


class Mecanico{
	private:
		vector<int> capacidad;
	public:

		vector<int> getCapacidad()const {return capacidad;};
		void addCapacidad(int cap){capacidad.push_back(cap);};
		int getCapacidad(int pos){  return capacidad[pos];};
};

/*
* Funcion que selecciona un mecanico 
* esta seleccion depende de la capacidad y de que no este asignado anteriormente.
*/

int seleccionMecanico(int averia, int pos, vector<Mecanico> mec, vector<int> asig){
    int tam = mec.size();
	for (int i = pos; i < tam; i++){
		int ave = mec.at(i).getCapacidad(averia);
    	if(ave==1)
    		if(asig.at(i)!=1)
				return i+1;
	}
    return 0;
}

/*
* Funcion Generar
* funcion que genera un nodo con una posible solucion.
*/
void generar(int nivel, vector<int> &s, vector<Mecanico> mecanicos, vector<int> &asignaciones ){
	
		int valor, mecanico;
		valor= s[nivel-1];
		mecanico = seleccionMecanico(nivel-1, valor, mecanicos, asignaciones);
		
		//si ningun mecanico tiene la capacidad para reparar la averia.
		if(mecanico > 0){
			s.at(nivel-1) = mecanico;
			asignaciones.at(mecanico-1) = 1;
		}else
			s.at(nivel-1) = mecanico;
		
		if (valor > 0 )
			asignaciones.at(valor-1) = 0;
}

/*
* Funcion retroceder
* se retrocede a la averia anterior para comprobar si existe
* otra posible solucion
*/
void retroceder(int &nivel, vector<int> &s, vector<int> &asig){
	int valor = s[nivel-1];
	s[nivel-1]=0;
	nivel--;
	if(valor > 0)
		asig.at(valor-1) = 0;
}

/*
* Funcion Valor
* cuenta la cantidad de mecanicos asignados;
*/
int valor(vector<int> solucion)
{
	vector<int>::iterator it = solucion.begin();
	int sol=0;
	for ( ; it != solucion.end(); ++it){
    	if(*it > 0 )
			sol++;
    }
    return sol;
}
/*
* Funcion Solucion
* llegaremos a una solucion cuando lleguemos a la ultima averia
*/
bool solucion(int nivel, int nivelMax ){
	if (nivel >= nivelMax )
		return true;
	return false;
}

/*
* Funcion Criterio
* comprobamos si a partir de la siguiente averia podemos encontrar una solucion. 
* se puede desplegar un nodo derecho
*/
bool criterio(int averia, int averiaMax, int mec){
	if( averia == averiaMax && mec < averiaMax)
		return false;

	return true;
}

/*
* Funcion masHermanos
* va a comprobar si para una misma averia 
* se puede desplegar un nodo derecho
* devuelve true si podemos desplegar un nodo derecho
*/

bool masHermanos(int averia, vector<int> s, vector<Mecanico> mecanicos, vector<int> asignaciones ){
	int mecanico;
	int valor = s[averia-1];
	mecanico = seleccionMecanico(averia-1, valor, mecanicos, asignaciones);
	if (mecanico != 0){
		return true;
	}
	return false;
}

/*
* Función no Recursiva del algoritmo backtracking
* encontrara una solucion y la imprimira por pantalla
* recibira 3 parametros
*    - Matriz con la capacidades de cada mecanico
*    - Número de averia a reparar
*    - Número de mecanicos disponibles.
* no devuelve nada
*/
void backtracking(vector<Mecanico> mecanicos, int nAverias,  int nMec){
	vector<int> S, mec_asig;
	S.assign(nAverias, 0);
	mec_asig.assign(nMec, 0);

	int nivelMax = nAverias;
	//nivel por el que va el algoritmo.
	int nivel=1;
	//estas variables son la que contienen la solucion optima.
	int voa = 0;
	vector<int> soa;
	soa.assign(nAverias, 0);
	int av_asig=0;

	while (nivel > 0 && voa != nAverias && voa != nMec) {

		generar(nivel, S, mecanicos, mec_asig);
		av_asig = valor(S);
		
		//se comprueba si la varaible solucion es una solucion y si es mas optima que la que tenemos
		if (solucion(nivel, nivelMax) && (av_asig > voa)){
			voa = av_asig;
			soa = S;
		}
		//comprobamos si podemos llegar a una solucion a partir del nodo actual
		else if (criterio(nivel,nivelMax, voa)){
			nivel++;
		}
		else {
			//se comprueba si existe mas hermanos.
			while(!masHermanos(nivel, S, mecanicos, mec_asig) && nivel > 0 )
				retroceder(nivel, S, mec_asig);
		}
	}
	cout << voa << endl;
	for (int i=0; i < nAverias; i++){
		cout << soa.at(i);
		if(i != nAverias-1)
			cout << " ";
	}
	cout << endl;
}




int main(int argc, char *argv[]){;

	int casos, nMecanicos, nAverias;
	cin >> casos;
	int c=0;

	cout << casos << endl;
	while (c < casos){
		cin >> nMecanicos;
		cin >> nAverias;

		vector<Mecanico> mecanicos;
		int cap;

		for (int i = 0; i < nMecanicos; i++) {
			Mecanico aux;
		 	for(int j=0; j< nAverias ; j++){
		 		cin >> cap;
		 		aux.addCapacidad(cap);
		 	}
		 	mecanicos.push_back(aux);
    	}
		backtracking(mecanicos, nAverias, nMecanicos);
		c++;

	}

	return 0;
}
