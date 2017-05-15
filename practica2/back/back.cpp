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
		int getCapacidad(int pos){
			return capacidad[pos];};

		void print(){
			vector<int>::iterator it = capacidad.begin();
			for ( ; it != capacidad.end(); ++it)
    				cout << *it;
			cout << endl;
		};


};

int seleccionMecanico(int averia, int pos, vector<Mecanico> mec, vector<int> asig){
    int tam = mec.size();
	for (int i = pos; i < tam; i++){
		int ave = mec.at(i).getCapacidad(averia);
		//cout << "m: "<< i << " averia:" << averia <<  " valor: "<<ave <<" -- " << asig.at(i)<< endl;
    	if(ave==1){
    		if(asig.at(i)!=1)
				return i+1;
		}
	}
    return 0;
}


void generar(int nivel, int nivelMax, vector<int> &s, vector<Mecanico> mecanicos, vector<int> &asignaciones ){
	
		int valor, mecanico;
		valor= s[nivel-1];
		//genera el nodo de la izquierda
		//if (valor==-1)
		//	valor = 0;
			//s[nivel-1]=0;
		//}
		//genera asignaciones con un mecanico
		//else{
			//cout << "valor:" << valor << endl;
		//if (nivel <= nivelMax ){
			mecanico = seleccionMecanico(nivel-1, valor, mecanicos, asignaciones);
		
		//si ningun mecanico tiene la capacidad para reparar la averia.
			if(mecanico > 0){
				s.at(nivel-1) = mecanico;
				asignaciones.at(mecanico-1) = 1;
			}else{
				s.at(nivel-1) = mecanico;
				//asignaciones.at(mecanico) = 1;

				
				if (valor > 0 )
					asignaciones.at(valor-1) = 0;
			}
			
		//}
			
}

/*
 Función que realiza el retroceso de un nivel una vez que se haya comprobado
 que no hayan más nodos que se puedan explorar en el nivel que recibe como
 parámetro.
*/
void retroceder(int &nivel, vector<int> &s, vector<int> &asig){
	// Pone el contenido del vector a -1 y retrocede un nivel
	//cout << "R:"<< nivel << endl;
	int valor = s[nivel-1];
	s[nivel-1]=0;
	nivel--;
	//cout << "R-->valor:" << valor << endl;
	if(valor > 0)
		asig.at(valor-1) = 0;
/*
	for (int i=0; i < asig.size(); i++){
				cout << asig.at(i);
				if(i != asig.size()-1)
					cout << " ";
			}
			cout << endl;*/
}
/*
* Funcion Valor
* cuenta la cantidad de mecanicos asignados
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

bool rep_mecanico(vector<int> solucion){
	int tam = solucion.size();
	for (int i = 0; i < tam-1; i++){
		if(solucion.at(i) > 0){
			for (int j = i+1; j < tam; j++){
    			if(solucion.at(i)  == solucion.at(j))
					return true;
			}
		}

    }

    return false;
}


/*
 * Nodo sera solucion si es terminal
 * Ademas se le añade
 */

bool solucion(int nivel, int nivelMax ){
	if (nivel >= nivelMax )//&& !rep_mecanico(solucion))
		return true;
	return false;
}
/*
* lo que hace el criterio es comprobar si se puede
* alcanzar una solucion valida desde s[1] hasta s[nivel]
* sino descarta todos los descendientes actuales
*/

bool criterio(int averia, int averiaMax, vector<Mecanico> mecanicos , vector<int> asignaciones){
	int mecanico;
 	mecanico = seleccionMecanico(averia, 0, mecanicos, asignaciones);

	//habra una solucion valida si la averia siguiente se puede asignar
	if (averia == averiaMax )//|| mecanico == 0)
		return false;

	return true;
}

/*
* Funcion masHermanos
* comprueba si existe mas nodos hermanos a generar
*/

bool masHermanos(int averia, vector<int> s, vector<Mecanico> mecanicos, vector<int> asignaciones ){
	int mecanico;
	int valor = s[averia-1];
	mecanico = seleccionMecanico(averia-1, valor, mecanicos, asignaciones);
	//cout << "mec -- H" << mecanico << endl;
	if (mecanico != 0){
		return true;
	}
	return false;
}

/*
 Función principal que devuelve el valor óptimo encontrado para el problema a partir de los datos de entrada
 que recibe como parámetro.
*/
void backtracking(vector<Mecanico> mecanicos, int nAverias,  int nMec){
	//cout << "-----------------------" << endl;
	//variable solucion que se inicializa a -1.
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

	while (nivel > 0 && voa != nAverias) {
		//funcion que genera un nodo hijo
		/*cout << "nivel: " << nivel << endl;
		for (int i=0; i < nAverias; i++){
				cout << S.at(i);
				if(i != nAverias-1)
					cout << " ";
			}
			cout << endl;*/

		generar(nivel, nivelMax, S, mecanicos, mec_asig);
		av_asig = valor(S);

		/*
		for (int i=0; i < nAverias; i++){
				cout << S.at(i);
				if(i != nAverias-1)
					cout << " ";
			}
			cout << endl;
		for (int i=0; i < nMec; i++){
				cout << mec_asig.at(i);
				if(i != nMec-1)
					cout << " ";
			}
			cout << endl;*/
		
		//se comprueba si la varaible solucion es una solucion y si es mas optima que la que tenemos
		if (solucion(nivel, nivelMax) && (av_asig > voa))
		{
			voa = av_asig;
			soa = S;
			//cout << "es una solucion"<< endl;
			//cout << "-----------------------" << endl;
		}
		//comprobamos si podemos llegar a una solucion a partir del nodo actual
		else if (criterio(nivel,nivelMax, mecanicos, mec_asig)){
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
	//retorna los segmentos activos de la solucion.
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
