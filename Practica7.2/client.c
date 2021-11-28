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
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include "randomFile.h"

#define PUERTO 55556

int main ()
{
    int sockdesc;
    struct sockaddr_in server_info;
    struct hostent *host;

    int numProcesses;
    int waitReadTime = 0;
    int remaining = 0;

    int nProccesToRead;
    int i = 0, processId, processPriority, processTExe;
    FILE* file;
    struct process process;

    srand (time (NULL));

    sockdesc = socket (AF_INET, SOCK_STREAM, 0);
    host = gethostbyname ("127.0.0.1");

    bcopy (host->h_addr, &server_info.sin_addr, host->h_length);
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons (PUERTO);

    numProcesses = generateRandomFile ();

    file = fopen ("randomFile.txt", "rb");
    connect (sockdesc, (struct sockaddr *) &server_info, sizeof (server_info));

    while (numProcesses > 0)
    {
        if (waitReadTime == 0 && remaining != -1)
        {
            
            nProccesToRead = rand () % 50 + 1;

            fseek (file, remaining, SEEK_SET);

            i = 0;
            while (i++ < nProccesToRead && feof (file) == 0)
            {
                
                fscanf (file, "%d %d %d\n", &processId, &processPriority, &processTExe);
                process = newProcess (processId, processPriority, processTExe);
                printf ("Leído el proceso con id: %d\n", process.id);
                write (sockdesc, &process, sizeof (struct process));
                
                numProcesses--;
                printf ("Faltan %d procesos por leer.\n", numProcesses);
            }
            
            remaining = (feof (file) != 0) ? -1 : ftell (file);
            waitReadTime = rand () % 30 + 1;
            
        }
        sleep (1);
        waitReadTime--;
    }
    fclose (file);
    close (sockdesc);
}