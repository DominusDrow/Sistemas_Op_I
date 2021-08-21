/**
 * PRACTICA 1: Listas ligadas circulares y archivos
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    201957903
 * 
*/
#include <stdio.h> 
#include <stdlib.h>

//Estructura del nodo 
struct Nodo{
    int num;
    struct Nodo *sig;
};

//Renombrar un puntero a la estructura del Nodo
typedef struct Nodo* nodo;

//Creacion de la lista ligada circular
nodo raiz=NULL;

/**
 * Funcion que devuelve 1 si la lista ligada circular 
 * esta vacia y 0 en caso contrario
 */
int vacia(){
    return (raiz == NULL) ?1 :0;
}

/**
 * Funcion que devuelve el numero de elementos que
 * tiene la lista ligada circular
 */
int tamanio(){
    int tam = 0;
    if (!vacia()){
        nodo aux = raiz;
        do {
            tam++;
            aux = aux->sig;
        } while (aux != raiz);
    }
    return tam;
}

/**
 * Funcion recibe una posicion y un elemento para insertarse
 * en la lista ligada circular, SI LA POSICION ES MAYOR AL NÚMERO
 * DE ELEMENTOS DE LA LISTA, EL ELEMENTO SE INSERATA AL FINAL
 * 
 * Parametros:
 * int posicion de la lista ligada
 * int nuevo elemento
 */
void insertar(int i,int num){
    nodo nuevo = malloc(sizeof(struct Nodo));
    nuevo->num = num;
    int j;

    if (vacia()){
        nuevo->sig = nuevo;
        raiz = nuevo;
    }
    else if (i!=1 && i <= tamanio()){
          
        nodo aux = raiz;
        for (j = 1; j <= i-2; j++)    //para en uno anterior 
            aux = aux->sig;        
        nodo anterior = aux;
        nodo siguiente = aux->sig;
        anterior->sig = nuevo;
        nuevo->sig = siguiente;
    }
    else{
        nodo ultimo = raiz;
        for (j = 1; j <= tamanio()-1; j++)  
            ultimo = ultimo->sig;    
        nuevo->sig = raiz;
        ultimo->sig = nuevo;

        if (i == 1)  raiz = nuevo;
    } 
}

/**
 * Funcion recibe una posicion de un elemento de la lista ligada 
 * circular para eliminarse, SI LA POSICION ES MAYOR AL NÚMERO
 * DE ELEMENTOS DE LA LISTA, NO SE ELIMINA NINGUN ELEMENTO
 * 
 * Parametros:
 * int posicion de la lista ligada
 */
void elminimar(int i){
    int j;
    if (i <= tamanio()){
        if (i == 1){
            if (tamanio() == 1){
                free(raiz);
                raiz = NULL;
            }
            else{
                nodo ultimo = raiz, aux = raiz;
                for (j = 1; j <= tamanio()-1; j++)  
                    ultimo = ultimo->sig; 
                raiz = raiz->sig;
                ultimo->sig = raiz;
                free(aux);
            }
        }
        else{
            nodo aux = raiz;
            for (j = 1; j <= i-2; j++)  //para en uno anterior 
                aux = aux->sig;
            nodo anterior = aux;
            nodo borrar = aux->sig;
            aux = aux->sig->sig;
            anterior->sig = aux;
            free(borrar);
        }
    }
}

/**
 * Funcion que busca un elemento dentro de la lista ligada
 * circular, si lo encuentra devuelve su posicion, en caso 
 * contrario devuelve 0
 * 
 * Parametros:
 * int elemento a buscar
 */
int buscar(int num){
    nodo aux = raiz;
    int j, i = 0;

    if(!vacia())
        for (j = 1; j <= tamanio(); j++){
            if(aux->num == num){
                i=j;
                break;
            }   
            else aux = aux->sig;
        }
               
    return i;
}

/**
 * Funcion que imprime todos los elementos de la lista 
 * ligada cicular a partir de la raiz
 */
void imprimir(){
    if (!vacia()){
        nodo aux = raiz;
        do {
            printf("=> %i ",aux->num);
            aux = aux->sig;
        } while (aux != raiz);
        printf("=>\n");
    }
}


/**
 * Funcion que libera la memoria utilizada por la lista ligada 
 * circular en la ejecucion del programa una vez que este halla 
 * finalizado.
 */
void liberarEspacio(){
   if (raiz != NULL){
        nodo borrar,aux = raiz->sig;
        while (aux != raiz){
            borrar = aux;
            aux = aux->sig;
            free(borrar);
        }
        free(raiz);
    }
}
