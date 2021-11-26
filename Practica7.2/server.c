#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "priorityQueue.h"

#define PUERTO 55556

void server (int cs);
void printProcessData (struct node* process);

int main ()
{
    int sockdesc; // El descriptor del socket.
    int cs; // El descriptor del socket que regresa la función accept
    struct sockaddr_in local;

    sockdesc = socket (AF_INET, SOCK_STREAM, 0);

    local.sin_family = AF_INET;
    local.sin_port = htons (PUERTO);
    local.sin_addr.s_addr = INADDR_ANY;

    bind (sockdesc, (struct sockaddr *) &local, sizeof (local));
    
    listen (sockdesc, 0);

    while (1)
    {
        cs = accept (sockdesc, (struct sockaddr *) 0, (int *) 0);
        server (cs);
        close (cs);
    }
}

void server (int cs)
{
    struct node process;
    int t;
    while (1)
    {
        t = read (cs, &process, sizeof (struct node));

        if (t == sizeof (struct node))
        { 
            // Push process node here
            printProcessData (&process); // just for testing
        }
    }
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