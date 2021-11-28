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
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int down(int semid, int noSem){
	struct sembuf s_buf;

	s_buf.sem_num=noSem;
	s_buf.sem_op=-1;
	s_buf.sem_flg=SEM_UNDO;

	if(semop(semid, &s_buf, 1)==-1){
		perror("down failed");
		exit(1);
	}else
		return 0;

}

int up(int semid, int noSem){
	struct sembuf s_buf;

	s_buf.sem_num=noSem;
	s_buf.sem_op=1;
	s_buf.sem_flg=SEM_UNDO;

	if(semop(semid, &s_buf, 1)==-1){
		perror("up failed");
		exit(1);
	}else
		return 0;

}
