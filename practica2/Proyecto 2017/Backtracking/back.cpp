#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class Trabajador{
	private:
		vector<int> capacidad;
		vector<bool> visitados;
		int max_trab;
	public:
		void addCapacidad(int cap){capacidad.push_back(cap);};
		int getCapacidad(int pos){  return capacidad[pos];};
		int get_maxTrab(){return max_trab;};
		void set_maxTrab(int max){ max_trab = max;};
		void reset_Visi(int trabajos){ 
					visitados.assign(trabajos, false);
		};
		void set_Visi(int trabajo, bool valor){ visitados.at(trabajo) = valor;};
		bool get_visit(int trabajo){ return visitados.at(trabajo);}
		void print_capacidad(){ 
		      vector<int>::iterator it = capacidad.begin(); 
		      for ( ; it != capacidad.end(); ++it) 
		            cout << *it << " ";
		       cout << endl;
	    }; 
	    void print_Visitados(){ 
		      vector<bool>::iterator it = visitados.begin(); 
		      for ( ; it != visitados.end(); ++it) 
		            cout << *it << " ";

		      cout << endl;
	    }; 
};


/*
* Funcion que selecciona un mecanico 
* esta seleccion depende de la capacidad y de que no este asignado anteriormente.
*/

int seleccionTrabajador(int nivel, vector<Trabajador> bw, vector<int> asig){
    int tam = bw.size();
    int bene_max = 0;
    int trab_bene_max = 0;
    int bene_trab = 0;

	for (int i = 0; i < tam; i++){
		//si el trabajador no ha sido asignado lo compruebo.
		if(!bw.at(i).get_visit(nivel) ){
			bene_trab = bw.at(i).getCapacidad(nivel);
    		if(bene_trab != 0 )
    			//compruebo si lo puedo asignar.
    			if(asig.at(i) < bw.at(i).get_maxTrab()){
    				if (bene_trab >= bene_max){
    					bene_max = bene_trab;
    					trab_bene_max = i+1;
    				}
    			}
    	}
	}
    return trab_bene_max;
}

/*
* Funcion Generar
* funcion que genera un nodo con una posible solucion.
*/
bool generar(int nivel, vector<int> &s, vector<Trabajador> &bw, vector<int> &asigna, int &bact ){
	int valor ;
		int nw = bw.size();

		valor = s[nivel];
	    s[nivel]++;
	    int capAnt =0;
	    if(valor != -1){
	    	capAnt = bw.at(valor).getCapacidad(nivel);
	        bact -= capAnt;
	        asigna.at(valor)--;
	    }
	    while((s[nivel] < nw)){
	    	int cap = bw.at(s[nivel]).getCapacidad(nivel);
	        if( cap > 0  && cap >= capAnt && asigna.at(s[nivel]) < bw.at(s[nivel]).get_maxTrab()){
	            asigna.at(s[nivel])++;
	            bact += cap;
	            return true;
	        }else{
	            s[nivel]++;
	        }
	    }
		return false;

}

/*
* Funcion retroceder
* se retrocede a la averia anterior para comprobar si existe
* otra posible solucion
*/
void retroceder(int &nivel, vector<int> &s, vector<int> &asig, vector<Trabajador> &bw,int &bact){
	int valor = s[nivel];
	s[nivel]=-1;

	nivel--;
	if(valor >= 0){
		asig.at(valor)--;
		bact -= bw.at(valor).getCapacidad(nivel+1);
	}
}

/*
* Funcion Solucion
* llegaremos a una solucion cuando lleguemos a la ultima averia
*/
bool solucion(int nivel, int nivelMax){
	if (nivel == nivelMax-1)
			return true;
	return false;
}

/*
* Funcion Criterio
* comprobamos si a partir de la siguiente averia podemos encontrar una solucion. 
* se puede desplegar un nodo derecho
*/
bool criterio(int nt, int ntmax, int voa, int bact, vector<int> cotaSuperior){
	if(nt < ntmax-1){
		if (voa < (bact + cotaSuperior[nt+1]))
			return true;

	}
	return false;
}

/*
* Funcion masHermanos
* va a comprobar si para una misma averia 
* se puede desplegar un nodo derecho
* devuelve true si podemos desplegar un nodo derecho
*/
bool masHermanos(vector<int> s, int nivel, int nw){
    return (s[nivel] < nw-1);
	
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
int backtracking(vector<Trabajador> bw, int nw, int nt, vector<int> cotaSuperior){
	//cout << "****************" << endl; 
	vector<int> S, trab_asig;

	S.assign(nt, -1); 
	trab_asig.assign(nw, 0); 


	//nivel por el que va el algoritmo.
	int nivel=0;
	
	int voa = 0; //beneficio optimo
	int bact =0; //beneficio actual

	while (nivel >= 0) {
		
		if(generar(nivel, S, bw, trab_asig, bact)  ){
				if (solucion(nivel, nt) && (bact > voa) ){
					voa = bact;
					if (cotaSuperior.at(0) == bact)
						return bact;
				}
				if (criterio(nivel, nt,voa, bact, cotaSuperior))
					nivel++;
				else {
					//se comprueba si existe mas hermanos.
					while(nivel >= 0 && !masHermanos(S, nivel,nw) )
						retroceder(nivel, S, trab_asig,bw,bact);
					
				}
		}else {
			//se comprueba si existe mas hermanos.
			S[nivel] = -1;
            nivel--;
		}
	}

	return voa;
}


int main(int argc, char *argv[]){;
	//numero de casos, trabajadores y trabajos
	int casos, nw, nt, cap;
	cin >> casos;
	int c=0;

	while (c < casos){
		cin >> nw;
		cin >> nt;

		vector<Trabajador> trabajadores;
		vector<int> cotas_sup;
		cotas_sup.assign(nt, 0);
		for (int i = 0; i < nw; i++) {
			Trabajador aux;
		 	for(int j=0; j< nt ; j++){
		 		cin >> cap;
		 		aux.addCapacidad(cap);
		 		if( cap > cotas_sup.at(j)){
                    cotas_sup.at(j) = cap;
		 		}
		 	}
		 	aux.reset_Visi(nt);
		 	trabajadores.push_back(aux);
    	}

    	int cant, voa;
    	//relleno la cantidad maxima de un trabajador
    	cap = 0;
    	for (int i = 0; i < nw; i++) {
		 	cin >> cant;
		 	trabajadores.at(i).set_maxTrab(cant);
		 	cap += cant;
    	}

    	// Recalculamos la cotaSuperior para cada tarea como la suma de ella más las anteriores
        // siendo la primera posición, la suma de todas las otras.
        for (int j = nt-2; j >= 0; j--){
            cotas_sup[j] += cotas_sup[j+1];
        }
       
	    if(cap >= nt){
			voa = backtracking(trabajadores, nw, nt, cotas_sup);
			cout << voa << endl;
	    	
    	}else
			cout << 0 << endl;

		c++;

	}

	return 0;
}
