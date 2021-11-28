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

void increase(int *i){
    if((*i)==ARRAY_LENGTH-1)
        *i=0;
     (*i)++;
}

int decrease(int i){
    if(i==0)
        return ARRAY_LENGTH-1;
    return --i;
}

int isEmpty(struct queue processesQueue){
    return processesQueue.head==processesQueue.end;
}

int isFull(struct queue processesQueue){
    if(processesQueue.end==ARRAY_LENGTH-1 && processesQueue.head==0)
        return 1;
    else
        return processesQueue.end==processesQueue.head-1;
}

void moveSince(struct queue *processesQueue, int i){
    int j=processesQueue->end, k;

    while(i!=j){
        k=decrease(j);
        processesQueue->processesArray[j]=processesQueue->processesArray[k];
        j=k;
    }
    increase(&processesQueue->end);
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
        int i=processesQueue->head, flg=0;
        
        while(i!=processesQueue->end){
            if(p.priority<processesQueue->processesArray[i].priority){
                moveSince(processesQueue, i);
                processesQueue->processesArray[i]=p;
                flg=1;
                break;
            }
            i++;
        }

        if(flg==0){
            processesQueue->processesArray[processesQueue->end]=p;
            increase(&processesQueue->end);
        }
        //printProcessData(p);
        processesQueue->lenght++;
        return 1;  
    }
    return 0;
}

int pushFirst(struct queue *processesQueue, struct process p){
    if(!isFull(*processesQueue)){
        processesQueue->head=decrease(processesQueue->head);
        processesQueue->processesArray[processesQueue->head]=p;
        processesQueue->lenght++;
        return 1;
    }
    return 0;
}

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
 * Funcion que devuelve el primer proceso en la cola que es el que
 * contiene el menor valor numerico en su campo "prioridad"
 * no recibe parametros.
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
