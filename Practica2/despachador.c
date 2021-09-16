#include "randomFile.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printProcessData (struct node* process);

int main() {
	int waitReadTime = 0;
	int remaining = 0;
	int numProcesses;

	struct node* process = NULL;
	struct node* last = NULL;

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

		if (last != process)
		{
			printf ("Cambio de contexto.\n");
		}

		process->remainingQuantum = process->remainingQuantum - 1;
		process->remainingTime = process->remainingTime - 1;
		printf ("Ahora ejecutando el proceso: %d\n", process->id);
		printf ("Tiempo de ejecucion restante: %d\n", process->remainingTime);
		printf ("Tiempo de quantum restante: %d\n", process->remainingQuantum);

		if (process->remainingTime == 0)
		{
			deleteFirst ();
			numProcesses--;
			process->tEnding = time (NULL);
			process->tWait = process->tEnding - process->tExe - process->tArrival;
			printf ("Proceso %d terminado.\n", process->id);
			printProcessData (process);
		}
		else
		{
			if (process->remainingQuantum == 0)
			{
				process->remainingQuantum = QUANTUM;
				deleteFirst ();
				pushLast (process);
			}
		}
		waitReadTime--;
		sleep (1);
	}

	freeSpace ();
}

void printProcessData (struct node* process)
{
	printf ("pid: %d\n", process->id);
	printf ("prioridad: %d\n", process->priority);
	printf ("tiempo de ejecucion: %d\n", process->tExe);
	printf ("tiempo de llegada: %d\n", process->tArrival);
	printf ("tiempo de espera: %d\n", process->tWait);
	printf ("tiempo de terminacion: %d\n", process->tEnding);
}