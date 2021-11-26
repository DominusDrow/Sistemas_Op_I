#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define LONG_MTX 50

int dead=0;

void deadSon(){
	dead=1;
}

int isNum(char cad[]){
	int lon=strlen(cad);
	int i;
	for(i=0; i<lon; i++){
		if(cad[i]<'0' || cad[i]>'9')
			return 1;
	}
	return 0;
}



int main(int argc, char **argv){

	if(argc!=2)
		exit(0);

	FILE* file=fopen(argv[1], "r");
	if(file!=NULL){
		
		char aryStrs[LONG_MTX][LONG_MTX];
		int p[2], p2[2], p3[2];
		int i=0, status, pid, pidHermano;
		
		if(pipe(p)<0 || pipe(p2)<0 || pipe(p3)<0){
			perror ("Error al crear la tuberia\n");
			exit(1);
		}

		struct sigaction act1;
		act1.sa_handler=&deadSon;

		switch(pidHermano=fork()){
			case -1:
				perror("Error al crear hijo 1\n");
				exit(1);
			case 0:
				close(p[0]);
				close(p2[1]);
				read(p2[0], &pidHermano, sizeof(int));
				while(!feof(file)){
					fscanf(file, "%s", aryStrs[i]);
					write(p[1], &i, sizeof(int));
					write(p[1],aryStrs[i], LONG_MTX);
					
					//lectura del hermano
					kill(pidHermano, SIGCONT);
					kill(getpid(), SIGSTOP);
					
					read(p2[0], &i, sizeof(int));
					
					i++;
				}
				kill(pidHermano, SIGUSR1);
				kill(pidHermano, SIGCONT);
				fclose(file);
				
				exit(0);

			default:

				switch(pid=fork()){
					case -1:
						exit(0);
					case 0:
						close(p[1]); //lee info de hermano
						close(p2[0]); //escribe al hermano
						close(p3[0]); //escribe al padre
						pid=getpid();
						write(p2[1], &pid, sizeof(int));

						while(1){
							read(p[0],&i,sizeof(int));
							read(p[0],aryStrs[i],LONG_MTX);

							if(isNum(aryStrs[i]))
								i--;
							
							write(p2[1], &i, sizeof(int));							

							kill(pidHermano, SIGCONT);
							kill(pid, SIGSTOP);

							sigaction(SIGUSR1, &act1, NULL);
							if(dead)
								break;
						}
						write(p3[1], &i, sizeof(int));
						write(p3[1], aryStrs, LONG_MTX*LONG_MTX);
						fclose(file);
						
						exit(0);
				}

		}

		fclose(file);
		while(wait(&status)!=pid);
		int j;

		close(p3[1]);

		read(p3[0], &i, sizeof(int));
		read(p3[0],aryStrs,LONG_MTX*LONG_MTX);
		
		printf("\npadre..................\n");
		for(j=0; j<=i; j++)
			printf("%s\n", aryStrs[j]);
		
		printf("......el padre muere.........\n");
		exit(0);
	}

}
