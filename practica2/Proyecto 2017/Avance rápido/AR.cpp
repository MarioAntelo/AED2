#include <stdlib.h>  // Funcion exit
#include <iostream>  // Variables cin y cout
#include <sys/time.h>
using namespace std;

#define MAX_ALUMNOS 100

////VARIABLES GLOBALES/////

struct pupitre{
       int alumno;
       int companero;       
};

pupitre Solucion[MAX_ALUMNOS/2];

int alumnoSolo;   //ENTERO CONTENEDOR DE ALUMNOS NO SENTADOS
int numAlumno;    //ENTERO CONTENEDOR DEL NÚMERO DE ALUMNOS

bool C[MAX_ALUMNOS];                   //ARRAY CONTENEDOR DE POSIBLES ALUMNOS
int Companero[MAX_ALUMNOS];            //ARRAYA CONTENEDOR DEL COMPAÑERO DE CADA ALUMNO

int Amistad[MAX_ALUMNOS][MAX_ALUMNOS]; // MATRIZ CONTENEDORA DE LOS VALORES DE AMISTAD
int Trabajo[MAX_ALUMNOS][MAX_ALUMNOS]; // MATRIZ CONTENEDORA DE LOS VALORES DE TRABAJO

int indiceSolucion;
int beneficioTotal;

///////////FUNCIONES ///////////

//FUNCION INICIA VARIABLES//
void resetearVariables(){
     alumnoSolo = 0;
     indiceSolucion = 0;
     beneficioTotal = 0;
     
     pupitre p;
     p.alumno = 0;
     p.companero = 0;
     for(int i = 0; i < MAX_ALUMNOS/2; i++){
             Solucion[i] = p;
     }
     
     for(int i = 0; i < MAX_ALUMNOS; i++){
             C[i] = 0;
             Companero[i] = -1;    //DISTINTO DE 0, YA QUE EL 0 REPRESENTA A UN COMPAÑERO
     }
     
     for(int i = 0; i < MAX_ALUMNOS; i++){
             for(int j = 0; j < MAX_ALUMNOS; j++){
                     Amistad[i][j] = 0;
                     Trabajo[i][j] = 0;        
             }
     }     
}

//METODO PARA INTRODUCIR VALORES DE LAS VARIABLES
void setVariables(int numAlumno){
     
     alumnoSolo = numAlumno;
       
     //MATRIZ AMISTAD
     for(int i = 0; i < numAlumno; i++){
             for(int j = 0; j < numAlumno; j++){
                     if(j == i){          //DIAGONAL MATRIZ = 0
                          Amistad[i][j] = 0;
                     }
                     else{
                          int amistad = 0;
                          cin >> amistad;
                          Amistad[i][j] = amistad;  
                     }        
             }        
     }    
     
     //MATRIZ TRABAJO
     for(int i = 0; i < numAlumno; i++){
             for(int j = 0; j < numAlumno; j++){
                     if(j == i){          //DIAGONAL MATRIZ = 0
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


//FUNCIÓN SELECCIONAR, ELIGIRÁ ALUMNO NO SENTADO ENTRE LOS CANDIDATOS

int seleccionar(){
    int i = 0;
    for(i = 0; i < numAlumno-1 && C[i] == true; i++){}
    if(i == numAlumno-1 && C[i] == true) i = -1;      //SI NO QUEDAN COMPAÑEROS DE PIE, DEVOLVEMOS -1
    return i;
}

//FUNCION POSIBLE, DEDICADA A BUSCAR COMPAÑEROS NO SENTADOS Y CALCULAR EL BENEFICIO


void posible(int alumno){
     
     int mejorCompanero;
     int beneficio = 0;
     int mayorBeneficio = 0;
     
     int companero = seleccionar(); //COMPAÑERO CON EL QUE EMPEZAR LA BÚSQUEDA
     mejorCompanero = companero;
     
     //SI NO QUEDAN COMPAÑEROS DE PIE
     if(companero == -1){
                Companero[alumno] = -1;              
     }
     else{
         
         for(; companero < numAlumno; companero++){  
                       
                 if(C[companero] == true){}
                 
                 else{      
                          beneficio = ( Amistad[alumno][companero] + Amistad[companero][alumno] ) 
                                             * ( Trabajo[alumno][companero] + Trabajo[companero][alumno] )  ;  
                                             
                          if(beneficio >= mayorBeneficio){       //COMPARAMOS EL BENEFICIO OBTENIDO CON EL DEL COMPAÑERO QUE YA TENÍAMOS, ACTUALIZAMOS EL BENEFICIO MÁXIMO
                                       mejorCompanero = companero;
                                       mayorBeneficio = beneficio;
                          }  
                  }     
                  
         }
         
          C[mejorCompanero] = true; //ENCONTRADO EL MEJOR COMPAÑERO, LO SENTAMOS
          
          pupitre p;
          p.alumno = alumno;
          p.companero = mejorCompanero;
          Solucion[indiceSolucion] = p;
          
          beneficioTotal += mayorBeneficio;
          
          alumnoSolo--;
         
     }
}

void ImprimirSolucion(){
     
     bool escogidos[numAlumno];
     int alumno;
     int companero;
     cout << beneficioTotal << endl;
     
     for(int i = 0 ; i < numAlumno/2-1; i++){
             alumno = Solucion[i].alumno;
             companero = Solucion[i].companero;
             escogidos[alumno] = true;
             escogidos[companero] = true;
             cout << alumno << " " << companero << " ";     
     }     
     alumno = Solucion[numAlumno/2-1].alumno;
     companero = Solucion[numAlumno/2-1].companero;
     escogidos[alumno] = true;
     escogidos[companero] = true;
     
     cout << alumno << " " << companero;
     if(numAlumno%2 != 0){
                   for(int i = 0; i < numAlumno; i++){
                           if(escogidos[i]!= true){
                                  cout << " " << i << endl;
                                  break;                   
                           }
                                   
                   }              
     }
     else cout << endl;
}

void voraz(){
     while(alumnoSolo != 0 ){
               
               int alumno = seleccionar();  //COGEMOS AL PRIMER ALUMNO NO SENTADO DE C
               
               C[alumno] = true;           //LO ELIMINAMOS DE LOS CANDIDATOS 
               alumnoSolo--;
               
               posible(alumno);           //BUSCAMOS COMPAÑERO AL ALUMNO
               
               indiceSolucion++;
                  
     }
     ImprimirSolucion();
     
}

int main(void){
    int numeroCasos;
    cin >> numeroCasos;
    while(numeroCasos >0){
            
            resetearVariables();
            cin >> numAlumno;
            setVariables(numAlumno); 
            voraz();

            numeroCasos--;
            
   }
   return 0;
}
