/**
 * PRACTICA 2: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    	    201957903
 * Pazos Quezada Azarel          	    201905195
 * Eusebio Aquino José Ángel 	 	    201969852
 * Javier Olivares Héctor 		        201938693
 * García Espinoza Alejandro Tonatiuh 	201910235
*/

#include <stdio.h>
#define QUANTUM 55
#define ARRAY_LENGTH 501

struct process
{
    int id;
    int priority;
    int tExe;
    int tArrival;
    int tWait;
    int tEnding;    
    int remainingTime;
    int remainingQuantum;
};

struct process newProcess(int id, int priority, int tExe){
	struct process p;
	p.id=id;
	p.priority=priority;
	p.tExe=tExe*1000;
	p.tArrival=0;
	p.tWait=0;
	p.tEnding=0;
	p.remainingTime=tExe;
	p.remainingQuantum=QUANTUM;
	return p;
}

void printProcessData(struct process p){
	printf("id=%d priority=%d tExe=%d tArrival=%d tWait=%d tEnding=%d remainingTime=%d remainingQuantum=%d\n", p.id, p.priority, p.tExe, p.tArrival, p.tWait, p.tEnding, p.remainingTime, p.remainingQuantum);
}
