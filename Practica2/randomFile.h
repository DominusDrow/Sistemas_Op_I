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


void lotReader(int* line){
    int n = rand () % 15 + 1;
    int total, i=0, flag, id, prority, tExe;

    FILE* file = fopen("randomFile.txt","rb");
    fseek(file,*line,SEEK_SET);
    printf("aaaa");
    while (i<n && feof(file)==0){
        fscanf(file,"%d %d %d", &id, &prority, &tExe);
        Create(id,prority,tExe);
        i++;
        printf("%d ",feof(file));
    }
    
    
    *line = ftell(file);
    flag = (feof!=0) ?0 :1;
    fclose(file);

}

