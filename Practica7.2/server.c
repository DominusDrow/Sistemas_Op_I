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

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "priorityQueue.h"
#include "upDown.h"

#define PUERTO 55556

void server (int semid, struct queue *queue, int cs);

int main ()
{
    int sockdesc; // El descriptor del socket.
    int cs; // El descriptor del socket que regresa la función accept
    struct sockaddr_in local;

    int shmid, semid, pid, i;
    struct process process, last;
    struct queue *queue;

    shmid = shmget (1, sizeof (struct queue), IPC_CREAT | IPC_EXCL |0600);
    if(shmid==-1)
    {
        perror ("shmget failed\n");
        exit (1);
    }
    
    if ((queue = (struct queue*) shmat (shmid, 0, 0)) == (struct queue*) -1)
    {
        perror ("shmat failed\n");
        exit (1);
    }

    semid = semget (1, 2, IPC_CREAT | IPC_EXCL |0600);
    if(semid==-1)
    {
        perror ("semget failed\n");
        exit (1);
    }
    
    up (semid, 1);

    queue->head = 0;
    queue->end = 0;
    queue->lenght = 0;

    pid = fork ();

    switch (pid)
    {
    case -1:
        perror ("error al crear hijo\n");
        exit (2);
        break;
    case 0:
        process = newProcess (-1, -1, -1);

        while (1)
        {
            down (semid, 0); // si hay procesos para despachar
            last = process;
            down (semid, 1); // entra a la región crítica
            process = pop (queue);
            up (semid, 1); 

            if (process.id == -1)
            {
                continue;
            }

            if (process.id != last.id)
            {
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
        exit (0);
        break;
    default:
        sockdesc = socket (AF_INET, SOCK_STREAM, 0);

        local.sin_family = AF_INET;
        local.sin_port = htons (PUERTO);
        local.sin_addr.s_addr = INADDR_ANY;

        bind (sockdesc, (struct sockaddr *) &local, sizeof (local));
        
        listen (sockdesc, 0);

        while (1)
        {
            cs = accept (sockdesc, (struct sockaddr *) 0, (int *) 0);
            server (semid, queue, cs);
            close (cs);
        }
        break;
    }
}

void server (int semid, struct queue *queue, int cs)
{
    struct process process;
    int t;
    while (1)
    {
        t = read (cs, &process, sizeof (struct process));
        if (t == sizeof (struct process))
        { 
            // Push process node here
            down (semid, 1);
            process.tArrival = time (NULL);
            push (queue, process);
            //printf ("%d\n", process.id);
            up (semid, 1);
            up (semid, 0);
        }
    }
}
