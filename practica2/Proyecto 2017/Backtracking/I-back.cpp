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
		int getCapacidad(int pos){return capacidad[pos];};
		void setCapacidad(int pos,int cap){
			capacidad[pos]= cap;
		};

		void print(){
			vector<int>::iterator it = capacidad.begin();
			for ( ; it != capacidad.end(); ++it)
    				cout << *it;
			cout << endl;
		};

		
};

int seleccionMecanico(vector<Mecanico> mec, int Averia, vector<int> asignados){
	for (int i=0; i < mec.size(); i++)
    	if(mec.at(i).getCapacidad(Averia)==1)
    		if(asignados[i] == 0)
				return i;
    return 0;
}

/*
* Función que realiza la generación de los nodos
* generara un nuevo nodo dependiendo de la capacidad de los mecanicos
*/
void generar(int nivel, vector<int> &s){
	/*int valor = -1;
	
	valor = seleccionMecanico(mecanicos,  nivel-1, asig);
	//si ningun mecanico tiene la capacidad para reparar la averia.
	s.at(nivel-1) = valor;

	int valor = s[nivel-1];
	*genera el nodo de la izquierda
	*/esa averia no se asignaria
	if (valor==-1){
		s[nivel-1]=0;

	}
	//genera el nodo de la derecha
	//donde se asigna a un tecnico
	else if(valor==0){
		s[nivel-1]+=1;
	}
}

/*
 Función que realiza el retroceso de un nivel una vez que se haya comprobado
 que no hayan más nodos que se puedan explorar en el nivel que recibe como 
 parámetro.
*/
void retroceder(int &nivel, vector<int> &s){
	// Pone el contenido del vector a -1 y retrocede un nivel
	s[nivel-1]=-1;
	nivel--;
}
/*
* Funcion Valor
* cuenta la cantidad de mecanicos asignados
*/
int valor(vector<int> solucios[nivel]+=1;n, vector<Mecanico> mecanicos)
{
	vector<int>::iterator it = solucion.begin();
	int sol=0;
	for ( ; it != solucion.end(); ++it){
    	if(*it != -1 )
			sol++;
    }
    return sol;
}



/*
 * Nodo sera solucion si es terminal
 */

bool solucion(int nivel, int nivelMax ){
	if (nivel >= nivelMax)
		return true;
	return false;
}

bool puedeAsignar(vector<Mecanico> mec, int Averia, vector<int> asignados){
	for (int i=0; i < mec.size(); i++)
    	if(mec.at(i).getCapacidad(Averia)==1)
    		if(asignados[i] == 1)
				return true;
    return false;
}


/*
* lo que hace el criterio es comprobar si se puede
* alcanzar una solucion valida desde s[1] hasta s[nivel]
* sino descarta todos los descendientes actuales
*/

bool criterio(int nivel, int nivelMax){
	
	//habra una solucion valida si la averia siguiente se puede asignar
	if (nivel == nivelMax || !puedeAsignar(nivle+1))
		return false;

	return true;
}

/*
* Funcion masHermanos
* comprueba si existe mas nodos hermanos a generar
*/

bool masHermanos(int nivel, vector<int> s){
	/*int valor = s[nivel-1];
	if (valor == 0){
		return true;
	}
	return false;*/
	return s[nivel] < s.size();
}

/*
 Función principal que devuelve el valor óptimo encontrado para el problema a partir de los datos de entrada
 que recibe como parámetro.
*/
int backtracking(vector<Mecanico> mecanicos, int nAverias){
	//variable solucion que se inicializa a -1.
	vector<int> S1;
	vector<int> mec_asig;
	S.assign(nAverias, -1);
	mec_asig.assign(mecanicos.size(), 0);

	int nivelMax = nAverias;
	//nivel por el que va el algoritmo.
	int nivel=1;
	//estas variables son la que contienen la solucion optima.
	int voa = 0;
	vector<int> soa;
	vector<int> mec_soa;

	while (nivel > 0) {
		//funcion que genera un nodo hijo
		generar(nivel, S, mecanicos, mec_asig);
		//se comprueba si la varaible solucion es una solucion y si es mas optima que la que tenemos
		if (solucion(nivel, nivelMax) && (valor(S) > voa))
		{
			cout << "Encontramos solucion"<<endl;
			voa = valor(S);
			soa = S;
		}
		//comprobamos si podemos llegar a una solucion a partir del nodo actual
		else if (criterio(nivel,nivelMax)){
			nivel++;
			cout << valor;
		}
		else {
			//se comprueba si existe mas hermanos.
			while(!masHermanos(nivel, S) && nivel > 0)
				retroceder(nivel, S);
		}
	}
	cout << endl << "solucion: ";
	for (int i=0; i < S.size(); i++)
		cout << S.at(i);
	cout << endl;
	//retorna los segmentos activos de la solucion.
	return nivelMax-valor(soa);
}




int main(int argc, char *argv[]){;
	
	int casos, nMecanicos, nAverias;
	cin >> casos;
	int c=0;

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
		 	aux.print();
    	}


		int sol;
		sol = backtracking(mecanicos, nAverias);
		
		cout << sol << endl;
		

		
		c++;
		
	}

	return 0;
}
