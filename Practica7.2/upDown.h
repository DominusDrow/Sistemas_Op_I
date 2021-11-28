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
