/**
 * PRACTICA 2: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    201957903
 * 
*/

#include <stdio.h> 
#include <stdlib.h>

//Estructura del nodo 
struct Node{    
    int id,prority,tExe,tArrival,tWait,tEnding,quantum;
    struct Node* next;
};

//Renombrar un puntero a la estructura del Nodo
typedef struct Node* node;

//Creacion de la lista ligada 
node root=NULL;

/**
 * Funcion que recibe una lista ligada y un nodo el cual 
 * lo ordena dentro de ella sugun su prioridad en forma 
 * acendente.
 * 
 * Parametros:
 * node lista ligada, nuevo nodo
 */
void push(node created){
    if(root==NULL)
        root = created;
    if(created->prority < root->prority){
        created->next = root->next;
        root = created;
    }
    else{
        node aux = root;

        while (created->prority > aux->prority && aux->next!=NULL)
            aux = aux->next;
        
        created->next = aux->next;
        aux->next = created;
    }
   
}

/**
 * Funcion que recibe una lista ligada y crea un nuevo nodo
 * dentro de ella, en donde los primeros tres parametros 
 * (identificar, prioridad y tiempo de ejecucion)
 * se igualan a los valores pasados por parametro.
 * 
 * Parametros:
 * node lista ligada
 * int identificador, prioridad, tiempo de ejecucion
 */
void Create(int id,int prority, int tExe){
    node created = malloc(sizeof(struct Node));
    created->id = id;
    created->prority = prority;
    created->tExe = tExe;
    created->next = NULL;
    push(created);
}

/**
 * Funcion que ddevuelve el nodo raiz que es el que
 * contiene el menor valor numerico en su campo "prioridad"
 * 
 * Parametros:
 * node lista ligada
 */
node pop( ){
    node aux = root;
    if(root!=NULL)
        root = root->next;

    return aux;
}

/**
 * Funcion que devuelve el numero de elementos que
 * tiene la lista ligada
 * 
 * Parametros:
 * node lista ligada
 */
int size(){
    int s = 0;
    if (root!=NULL){
        node aux = root;
        do {
            s++;
            aux = aux->next;
        } while (aux != NULL);
    }
    return s;
}

/**
 * Funcion que libera la memoria utilizada por la lista ligada 
 * circular en la ejecucion del programa una vez que este halla 
 * finalizado.
 */
void freeSpace(){
   if (root != NULL){
        node delate,aux = root->next;
        while (aux != root){
            delate = aux;
            aux = aux->next;
            free(delate);
        }
        free(root);
    }
}

void imprimir(){
    if (root!=NULL){
        node aux = root;
        do {
            printf("=> %i ",aux->id);
            aux = aux->next;
        } while (aux != NULL);
        printf("=>\n");
    }
}