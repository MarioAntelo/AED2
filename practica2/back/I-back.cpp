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

		void setCapacidad(vector<int> cap){
			int size = cap.size();
			for (int i=0 ; i < size; i++){
				if(cap[i]==0)
    					capacidad[i] = 0;
    			else if (cap[i]==-1)
    				i=size;
    			
    		}
		}

		bool igual(Mecanico aux){
			int size = capacidad.size();
			for (int i=0 ; i < size; ++i){
				if(capacidad[i] != aux.getCapacidad(i))
					return false;
			}
			return true;
		};
};

/*
* Función que realiza la generación de los nodos
* genera los hermanos o el primero para el nivel actual.
*/
void generar(int nivel, vector<int> &s){
	int valor = s[nivel-1];
	//genera el nodo de la izquierda
	if (valor==-1){
		s[nivel-1]=0;

	}
	//genera el nodo de la derecha
	else if(valor==0){
		s[nivel-1]=1;
	}
	
}

/*
 Función que realiza el retroceso de un nivel una vez que se haya comprobado
 que no hayan más nodos que se puedan explorar en el nivel que recibe como 
 parámetro.
/
void retroceder(int &nivel, vector<int> &s){
	// Pone el contenido del vector a -1 y retrocede un nivel
	s[nivel-1]=-1;
	nivel--;
}
/*
* Funcion Valor
* cuenta la cantidad de segmentos apagados de la solucion
/
int valor(vector<int> solucion)
{
	vector<int>::iterator it = solucion.begin();
	int sol=0;
	for ( ; it != solucion.end(); ++it){
    	if(*it == 0 )
			sol++;
    }
    return sol;
}

/*
* Comprobar simbolos
* compruebas todos los simbolos apagando los segmentos dañados de la solucion
* si hay dos simbolos iguales entonces devuelve true
* en caso contrario devuelve false
/

bool ComprobarSimbolos(vector<int> s, vector<Simbolo> simbolos){
	vector<Simbolo>::iterator it, it2;
	it = simbolos.begin();
	bool result;

	//modifico los simbolos apagando los segmentos que tiene la solucion
	for ( ; it != simbolos.end(); ++it)
		it->setSegmentos(s);

	it= simbolos.begin();
	//compruebo que todos los simbolos sean distintos.
	for ( ; it != simbolos.end(); ++it){
		it2 = it +1;
		for ( ; it2 != simbolos.end(); ++it2){
			result = it->igual(*it2);
			if(result){
				return true;
			}
		}

    }
    return false;
}

/*
* Sera nodo solucion si es un nodo terminal 
* y todos los simbolos son distintos con los segmentos 
* de la solucion que esten apagados
/
bool solucion(int nivel, int nivelMax,vector<int> s, vector<Simbolo> simbolos ){
	if ( (nivel >= nivelMax) && !ComprobarSimbolos(s, simbolos))
		return true;
	return false;
}



/*
* lo que hace el criterio es comprobar si se puede
* alcanzar una solucion valida desde s[1] hasta s[nivel]
* sino descarta todos los descendientes actuales
* si los primeros n/2 segmentos estan apagados se poda.
/

bool criterio(int nivel, int nivelMax,vector<int> s, vector<Simbolo> simbolos){
	
	//si los simbolos con los segmentos apagados son iguales entonces el criterio 
	//devuelve un false ya que no consigue una posible solucion
	if(ComprobarSimbolos(s, simbolos) || nivel == nivelMax)
		return false;

	return true;
}

/*
* Funcion masHermanos
* comrpueba si existe mas nodos hermanos a generar
/

bool masHermanos(int nivel, vector<int> s){
	int valor = s[nivel-1];
	if (valor == 0){
		return true;
	}
	return false;
}

/*
 Función principal que devuelve el valor óptimo encontrado para el problema a partir de los datos de entrada
 que recibe como parámetro.
*/
int backtracking(vector<Mecanico> mecanicos, int nAverias){
	//variable solucion que se inicializa a -1.
	vector<int> S;
	S.assign(nAverias, -1);

	int nivelMax = nAverias;
	//nivel por el que va el algoritmo.
	int nivel=1;
	//estas variables son la que contienen la solucion optima.
	int voa = 0;
	vector<int> soa; 

	while (nivel > 0) {
		//funcion que genera un nodo hijo
		generar(nivel, S);
		
		//se comprueba si la varaible solucion es una solucion y si es mas optima que la que tenemos
		if (solucion(nivel, nivelMax, S, mecanicos) && (valor(S) > voa))
		{
			voa = valor(S);
			soa = S;
		}
		//comprobamos si podemos llegar a una solucion a partir del nodo actual
		else if (criterio(nivel,nivelMax ,S, mecanicos))
			nivel++;			
		else {
			//se comprueba si existe mas hermanos.
			while(!masHermanos(nivel, S) && nivel > 0)
				retroceder(nivel, S);
		}
	}
	S.print();
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
    	}
		int sol;
		/*sol = backtracking(mecanicos, nAverias);
		
		cout << sol << endl;
		*/

		vector<Mecanico>::iterator it = mecanicos.begin();
			for ( ; it != mecanicos.end(); ++it)
    				it->print();
			cout << endl;

		c++;
		
	}

	return 0;
}
