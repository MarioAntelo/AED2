#include <stdlib.h>  // Funcion exit
#include <iostream>  // Variables cin y cout
#include <sys/time.h>
using namespace std;

#define MAX_ALUMNOS 100

///////////////////////////////////////////////////////////
//////////        VARIABLES GLOBALES        ///////////////
///////////////////////////////////////////////////////////

struct pupitre{
       int alumno;
       int companero;       
};

pupitre Solucion[MAX_ALUMNOS/2];

int alumnosSinPupitre;   //Entero que va a contener los alumnos que todavía no han sido sentados
int NAlumnos;            //Entero que va a contener el numero de alumnos

bool C[MAX_ALUMNOS];                   //Array de booleanos que va a contener los alumnos candidatos(false si el alumno aun no ha sido sentado)
int Companero[MAX_ALUMNOS];            //Array que va a contener el compañero de cada alumno(Inicializado a -1, porque 0 es un alumno)

int Amistad[MAX_ALUMNOS][MAX_ALUMNOS]; // Matriz que contiene los valores de amistad de los alumnos
int Trabajo[MAX_ALUMNOS][MAX_ALUMNOS]; // Matriz que contiene los valores de trabajo de los alumnos

int indiceSolucion;
int beneficioTotal;
///////////////////////////////////////////////////////////
///////////       FUNCIONES DEL PROGRAMA        ///////////
///////////////////////////////////////////////////////////

/*Funcion que va a inicializar las variables globales*/
void resetearVariables(){
     alumnosSinPupitre = 0;
     indiceSolucion = 0;
     beneficioTotal = 0;
     
     
     for(int i = 0; i < MAX_ALUMNOS/2; i++){
              pupitre p;
              p.alumno = 0;
              p.companero = 0;
            Solucion[i] = p;
     }
     
     for(int i = 0; i < MAX_ALUMNOS; i++){
             C[i] = 0;
             Companero[i] = -1;    //No lo ponemos a 0 porque el 0 es un compañero
     }
     
     for(int i = 0; i < MAX_ALUMNOS; i++){
             for(int j = 0; j < MAX_ALUMNOS; j++){
                     Amistad[i][j] = 0;
                     Trabajo[i][j] = 0;        
             }
     }     
}

//Metodo que va a introducir los valores de las variables(Matrices, arrays,...)
void setVariables(int nAlumnos){
     
     alumnosSinPupitre = NAlumnos;
       
     //Matriz Amistad
     for(int i = 0; i < nAlumnos; i++){
             for(int j = 0; j < NAlumnos; j++){
                     if(j == i){          //La diagonal de las matrices es 0
                          Amistad[i][j] = 0;
                     }
                     else{
                          int amistad = 0;
                          cin >> amistad;
                          Amistad[i][j] = amistad;  
                     }        
             }        
     }    
     
     //Matriz Trabajo
     for(int i = 0; i < nAlumnos; i++){
             for(int j = 0; j < NAlumnos; j++){
                     if(j == i){          //La diagonal de las matrices es 0
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


/*La función seleccionar se va a encargar de escoger, de entre los alumnos candidatos(C), 
  el primer alumno que encontremos que no esté sentado*/
int seleccionar(){
    int i = 0;
    for(i = 0; i < NAlumnos-1 && C[i] == true; i++){}
    if(i == NAlumnos-1 && C[i] == true) i = -1;      //Si no quedan mas alumnos de pie, se devuelve -1
    return i;
}

/* La funcion factible se va a encargar de, dado un alumno, buscar todos los compañeros que no hayan sido
   ya sentados, y calcular el beneficio que obtendría con cada alumno. Vamos a ir modificando el compañero 
   que asignaremos si vamos encontrando un compañero con el que se obtenga mayor beneficio.
*/
void factible(int alumno){
     
     int mejorCompanero;
     int beneficio = 0;
     int mayorBeneficio = 0;
     
     int companero = seleccionar(); //Conseguimos el compañero por el que empezar a buscar
     mejorCompanero = companero;
     
     //Si no quedan mas alumnos de pie
     if(companero == -1){
                Companero[alumno] = -1;              
     }
     else{
         
         for(; companero < NAlumnos; companero++){  
                       
                 if(C[companero] == false){      
                          beneficio = ( Amistad[alumno][companero] + Amistad[companero][alumno] ) 
                                             * ( Trabajo[alumno][companero] + Trabajo[companero][alumno] )  ;  
                                             
                          if(beneficio >= mayorBeneficio){                //Si el beneficio que obtenemos con el compañero que estamos tratando es mayor que
                                                                         //el beneficio que teniamos, actualizaremos el compañero y el beneficio maximo
                                       mejorCompanero = companero;
                                       mayorBeneficio = beneficio;
                          }  
                  }     
                  
         }
         
          C[mejorCompanero] = true; //Sentamos al mejor compañero que hayamos encontrado
          
          pupitre p;
          p.alumno = alumno;
          p.companero = mejorCompanero;
          Solucion[indiceSolucion] = p;
          
          beneficioTotal += mayorBeneficio;
          
          alumnosSinPupitre--;
         
     }
}

void printSolucion(){
     
     bool escogidos[NAlumnos];
     int alumno;
     int companero;
     cout << beneficioTotal << endl;
     
     for(int i = 0 ; i < (NAlumnos/2)-1; i++){
             alumno = Solucion[i].alumno;
             companero = Solucion[i].companero;
             escogidos[alumno] = true;
             escogidos[companero] = true;
             cout << alumno << " " << companero << " ";     
     }     
     alumno = Solucion[(NAlumnos/2)-1].alumno;
     companero = Solucion[(NAlumnos/2)-1].companero;
     escogidos[alumno] = true;
     escogidos[companero] = true;
     
     cout << alumno << " " << companero;
     if(NAlumnos%2 != 0){
                   for(int i = 0; i < NAlumnos; i++){
                           if(escogidos[i]!= true){
                                  cout << " " << i << endl;
                                  break;                   
                           }
                                   
                   }              
     }
     else cout << endl;
}

void voraz(){
     while(alumnosSinPupitre > 0 ){
               
               int alumno = seleccionar();  //Se escoge, de entre C, el primer alumno que no esté sentado
               
               C[alumno] = true;           //El alumno se elimina del conjunto de candidatos  
               alumnosSinPupitre--;
               
               factible(alumno);           //Se busca un companero al alumno
               
               indiceSolucion++;
                  
     }
     printSolucion();
     
}

int main(void){
    int numeroCasos;
    cin >> numeroCasos;
    while(numeroCasos >0){
            
            resetearVariables();
            cin >> NAlumnos;
            setVariables(NAlumnos); 
            voraz();

            numeroCasos--;
            
   }
   return 0;
}
