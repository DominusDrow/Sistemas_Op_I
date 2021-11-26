/**
 * PRACTICA 7: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    	    201957903
 * Pazos Quezada Azarel          	    201905195
 * Eusebio Aquino José Ángel 	 	    201969852
 * Javier Olivares Héctor 		        201938693
 * García Espinoza Alejandro Tonatiuh 	201910235
*/

/***MANEJO DE ARCHIVOS (GENERARDOR Y LECTURA DE PROCESOS)***/

#include <stdio.h> 
#include <stdlib.h>
#include "priorityQueue.h"

/**
 * Funcion que crea el archivo "randomFile.txt" con datos 
 * aleatorios y devuelve el numero de procesos creados,
 * no recibe parametros
 */
int generateRandomFile(){
    int processes  = rand () % 499 + 2;
    int i, id, prority, tExe;

    FILE* file = fopen("randomFile.txt","wb");

    for ( i = 0; i < processes; i++){
        id = rand () % 9000 + 1000;
        prority = rand () % 33 + 0;  
        tExe = rand () % 200 + 1;       
        fprintf(file,"%d %d %d\n",id,prority,tExe); 
    }
    fclose(file);
    
    //creamos el archivo donde se almacenaran los resultados
    FILE* fileI = fopen("infoProcess.txt","wb"); 
    fprintf(fileI," ID  P      A    WAIT   END");
    fclose(fileI);

    return processes;
}

/**
 * Funcion que lee n siguientes lineas del archivo "randomFile.txt"
 * cada vez que es invocada hasta que llegue al final del archivo 
 * 
 * Parametros:
 * int* linea en que se quedo leyendo
 */
void lotReader(int* line){
    int n = rand () % 50 + 1;
    int i=0, id, priority, tExe;

    FILE* file = fopen("randomFile.txt","rb");
    fseek(file,*line,SEEK_SET);

    while (i++ < n && feof(file) == 0){
        fscanf(file,"%d %d %d\n", &id, &priority, &tExe);
        create (id, priority, tExe);
    }
    
    *line = (feof(file)!=0) ?-1 :ftell(file);
    fclose(file);
}

/**
 * Funcion que crea el archivo "infoProcess.txt" y va
 * escribiendo los procesos en orden de finalizacion,
 * no recibe parametros.
 */
void writeProcess(struct node* process){
    FILE* file = fopen("infoProcess.txt","ab");
    fprintf(file,"\n%d %d %d %d %d", process->id, process->priority, process->tArrival, process->tWait, process->tEnding);
    fclose(file);
}

