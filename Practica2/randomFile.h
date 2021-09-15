/**
 * PRACTICA 2: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    201957903
 * 
*/

#include <stdio.h> 
#include <stdlib.h>
#include "priorityQueue.h"

void generateRandomFile(){


}

/**
 * Funcion que lee n siguientes lineas del archivo "randomFile.txt"
 * cada vez que es invocada hasta que llegue al final del archivo 
 * 
 * Parametros:
 * int* linea en que se quedo leyendo
 */
void lotReader(int* line){
    int n = rand () % 15 + 1;
    int i=0, id, prority, tExe;

    FILE* file = fopen("randomFile.txt","rb");
    fseek(file,*line,SEEK_SET);

    while (i++ < n && feof(file) == 0){
        fscanf(file,"%d %d %d", &id, &prority, &tExe);
        Create(id,prority,tExe);
    }
    
    *line = (feof(file)!=0) ?-1 :ftell(file);
    fclose(file);
}

