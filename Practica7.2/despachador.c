#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "priorityQueue.h"
#include "upDown.h"

int main(){
	int shmid, semid, pid, i;
	struct process process, last;
	struct queue *queue;

	shmid=shmget(1, sizeof(struct queue), IPC_CREAT|0600);
	if((queue=(struct queue*)shmat(shmid,0,0))==(struct queue *)-1){
		perror("shmat failed\n");
		exit(1);
	}

	semid=semget(1, 2, IPC_CREAT|0600);
	up(semid, 1);

	queue->head=0;
	queue->end=0;
	queue->lenght=0;

	pid=fork();
	switch(pid){
		case -1:
			perror("error al crear hijo\n");
			exit(2);
		case 0:
			
			process=newProcess(-1,-1,-1);

			while(1){
				down(semid, 0); //si hay procesos para despachar
				last=process;
				down(semid, 1); //entra a la región crítica
				process=pop(queue);
				up(semid, 1); // sale de la región crítica
				
				if(process.id!=last.id){
					printf ("\n*** CAMBIO DE CONTEXTO ***\n\n");
					sleep (1);
				}
				

				process.remainingQuantum--;
				process.remainingTime--;
				printf ("Ahora ejecutando el proceso: %d\n", process.id);
				printf ("Prioridad: %d\n", process.priority);
				printf ("Tiempo de ejecucion restante: %d\n", process.remainingTime);
				printf ("Tiempo de quantum restante: %d\n", process.remainingQuantum);
				sleep (1);

				if (process.remainingTime == 0)
				{
					process.tEnding = time (NULL) ;
					process.tWait = process.tEnding - process.tExe - process.tArrival;
					printf ("\nPROCESO TERMINADO.\n");
					printProcessData(process);
					//writeProcess(process);
				}
				else if (process.remainingQuantum == 0)
				{
					process.remainingQuantum = QUANTUM;
					down(semid, 1);
					pushLast(queue,process);
					up(semid, 1);
					up(semid,0);
				}
				else
				{
					down(semid, 1);
					pushFirst(queue, process);
					up(semid, 1);
					up(semid,0);
				}
				
			}

			exit(0);
	}
	
	printf("antes de la region\n");
	down(semid, 1);
	printf("adentro de la region\n");
	process=newProcess(1, 3, 5);
	push(queue, process);
	up(semid,0);

	process=newProcess(2, 2, 6);
	push(queue, process);
	up(semid,0);

	process=newProcess(3, 1, 7);
	push(queue, process);
	up(semid,0);

	process=newProcess(4, 4, 3);
	push(queue, process);
	up(semid,0);

	up(semid, 1);
	printf("afuera de la region\n");

	for(i=0; i<queue->lenght; i++)
		printProcessData(queue->processesArray[i]);

	wait((int *)0);

	semctl(semid, 0, IPC_RMID);
	shmdt(queue);
	shmctl(shmid, IPC_RMID, NULL);

	exit(0);
}
