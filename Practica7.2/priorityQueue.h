/**
 * PRACTICA 2: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    	201957903
 * Pazos Quezada Azarel          	201905195
 * Eusebio Aquino José Ángel 	 	201969852
 * Javier Olivares Héctor 		201938693
 * García Espinoza Alejandro Tonatiuh 	201910235
*/

/***SIMULADOR DE PLANIFICACIÓN A LARGO PLAZO***/

#include <stdlib.h>
#include "process.h"

//Estructura del nodo 
struct queue
{
    struct process processesArray[ARRAY_LENGTH];
    int head;
    int end;
    int lenght;
};

/**
 * Funcion que incrementa el valor
 * de una variable tomando de referencia
 * la cola
 */

void increase(int *i){
    if((*i)==ARRAY_LENGTH-2)
        *i=0;
    else
        (*i)++;
}

/**
 * Funcion que decrementa el valor
 * de una variable tomando de referencia
 * la cola
 */

void decrease(int *i){
    if((*i)==0)
        *i=ARRAY_LENGTH-2;
    else
        (*i)--;
}

/**
 * Funcion que pregunta si la cola esta vacia
 */

int isEmpty(struct queue processesQueue){
    return processesQueue.head==processesQueue.end;
}

/**
 * Funcion que pregunta si la cola esta llena 
 */

int isFull(struct queue processesQueue){
    if(processesQueue.end==ARRAY_LENGTH-1 && processesQueue.head==0)
        return 1;
    else
        return processesQueue.end==processesQueue.head-1;
}

/**
 * Funcion que desplaza los procesos de la cola
 * hacia la derecha a partir de el proceso
 * que se ecnuentra en el indice i
 */

void moveSince(struct queue *processesQueue, int i){
    int j=processesQueue->end, k;
    k=j;

    while(i!=j){
        decrease(&k);
        processesQueue->processesArray[j]=processesQueue->processesArray[k];
        j=k;
    }
    increase(&processesQueue->end);
}

/**
 * Funcion que desplaza los procesos de la cola
 * hacia la izquierda a partir de el proceso
 * que se ecnuentra en el indice i
 */

void moveBackSince(struct queue *processesQueue, int i){
    int j, k;

    decrease(&processesQueue->head);
    j=processesQueue->head;
    k=j;
    while(i!=j){
        increase(&k);
        processesQueue->processesArray[j]=processesQueue->processesArray[k];
        j=k;
    }
    
}

/**
 * Funcion que recibe  un proceso el cual lo coloca
 * al inicio de la cola.
 */

int pushFirst(struct queue *processesQueue, struct process p){
    if(!isFull(*processesQueue)){
        decrease(&processesQueue->head);
        processesQueue->processesArray[processesQueue->head]=p;
        processesQueue->lenght++;
        return 1;
    }
    return 0;
}

/**
 * Funcion que recibe  un proceso el cual lo coloca
 * al final de la cola.
 */

int pushLast(struct queue *processesQueue, struct process p){
    if(!isFull(*processesQueue)){
        processesQueue->processesArray[processesQueue->end]=p;
        increase(&processesQueue->end);
        processesQueue->lenght++;
        return 1;
    }
    return 0;
}

/**
 * Funcion que recibe  un proceso el cual lo ordena dentro de
 * la cola sugun su prioridad en forma acendente.
 */

int push(struct queue *processesQueue, struct process p){
    if(isEmpty(*processesQueue)){
        processesQueue->processesArray[processesQueue->head]=p;
        increase(&processesQueue->end);
        processesQueue->lenght++;
        return 1;
    }else if(!isFull(*processesQueue)){
        int aux=processesQueue->end;

        decrease(&aux);

        if(p.priority < processesQueue->processesArray[processesQueue->head].priority){
            pushFirst(processesQueue, p);
        }else if(p.priority > processesQueue->processesArray[aux].priority){
            pushLast(processesQueue, p);
        }else{
            
            int i=processesQueue->head;
            int c=2;
            
            increase(&i);

            while(i!=processesQueue->end){
                if(p.priority<processesQueue->processesArray[i].priority){

                    if(c>=(processesQueue->lenght/2))
                        moveSince(processesQueue, i);
                    else
                        moveBackSince(processesQueue, i);

                    processesQueue->processesArray[i]=p;
                    processesQueue->lenght++;
                    return 1;
                }
                increase(&i);
                c++;
            }
        }
        return 1;  
    }
    return 0;
}

/**
 * Funcion que devuelve el primer proceso en la cola que es el que
 * contiene el menor valor numerico en su campo "prioridad".
 */


struct process pop(struct queue *processesQueue){

    if(isEmpty(*processesQueue))
        return newProcess(-1,-1,-1);
    
    struct process aux;
    aux=processesQueue->processesArray[processesQueue->head];
    increase(&processesQueue->head);
    processesQueue->lenght--;
    return aux;
}
