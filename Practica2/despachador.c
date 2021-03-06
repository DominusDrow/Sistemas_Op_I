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

/***SIMULADOR DE PLANIFICACIÓN A CORTO PLAZO***/

#include "randomFile.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printProcessData (struct node* process);

int main() {
	int time0 = time(NULL);
	int waitReadTime = 0;
	int remaining = 0;
	int numProcesses;

	struct node* process = NULL;
	struct node* last = NULL;
	
	srand(time(NULL));

	numProcesses = generateRandomFile ();

	while (numProcesses > 0)
	{
		if (waitReadTime == 0 && remaining != -1)
		{
			lotReader (&remaining); 
			waitReadTime = rand () % 30 + 1;
		}
		last = process;
		process = pop ();

		if (last != process && last !=NULL)
		{
			printf ("\n*** CAMBIO DE CONTEXTO ***\n\n");
			sleep (1);
		}

		//aqui es donde se simula que esta en ejecucion el proceso
		process->remainingQuantum--;
		process->remainingTime--;
		printf ("Ahora ejecutando el proceso: %d\n", process->id);
		printf ("Prioridad: %d\n", process->priority);
		printf ("Tiempo de ejecucion restante: %d\n", process->remainingTime);
		printf ("Tiempo de quantum restante: %d\n", process->remainingQuantum);	
		waitReadTime--;
		sleep (1);
		
		if (process->remainingTime == 0)
		{
			deleteFirst ();
			numProcesses--;
			process->tEnding = time (NULL) ;
			process->tWait = process->tEnding - process->tExe - process->tArrival;
			printf ("\nPROCESO TERMINADO.\n");
			printProcessData (process);
			writeProcess (process);
			free (process);
		}
		else if (process->remainingQuantum == 0)
		{
			process->remainingQuantum = QUANTUM;
			deleteFirst ();
			pushLast (process);
		}
	}
	resultsProcess();
	freeSpace ();
}

void printProcessData (struct node* process)
{
	printf ("id: %d\n", process->id);
	printf ("prioridad: %d\n", process->priority);
	printf ("tiempo de ejecucion: %d\n", process->tExe);
	printf ("tiempo de llegada: %d\n", process->tArrival);
	printf ("tiempo de espera: %d\n", process->tWait);
	printf ("tiempo de terminacion: %d\n", process->tEnding);
}
