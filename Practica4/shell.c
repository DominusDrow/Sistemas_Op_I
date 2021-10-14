/**
 * PRACTICA 4: Simulador de shell con fork() y exec()
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    	    201957903
 * Pazos Quezada Azarel          	    201905195
 * Eusebio Aquino José Ángel 	 	    201969852
 * Javier Olivares Héctor 		        201938693
 * García Espinoza Alejandro Tonatiuh 	201910235
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//definimos maximos para el comado y para los argumentos
#define maxChar 50
#define maxArgs 5

int main( ){

	char cmd[maxChar];
	char *args[maxArgs];
	int i,pid,status;

	while (1) {
		i=0;
		printf("~$ ");
		fflush(stdin); 								//limpiamos el buffer del teclado 
		memset(cmd, 0, maxChar); 			//limpiamos la cadena del comando anterior
		fgets(cmd, maxChar, stdin); 	//leemos una linea
		cmd[strcspn(cmd, "\n")] = 0; 	//cortamos hasta donde se hizo un salto de linea

		if(strlen(cmd)>0){

			//separamos el comando y los argumentos (parametros para la funcion execvp)
			args[i]=strtok(cmd, " ");
			while((args[++i] = strtok(NULL, " ")) != NULL);	

			if(strcmp(args[0],"salir") == 0)
				break;

			pid= fork();
			if(pid == -1)
				perror("no se pudo crear hijo");
			else if(pid == 0){
				status = execvp(args[0], args);	

				if(status){
					printf("\nComando no reconocido\n");
					exit(-1);
				}
			}
			else {
				while(wait(&status) != pid);
				if(WIFEXITED(status)){
					if(WEXITSTATUS(status) == 7)
						printf("**El proceso %d  termino debido que hay una division entre 0**\n",pid);
					else
						printf("**El proceso %d  termino normalmente**\n",pid);
				}
				if(WIFSIGNALED(status))
					printf("**El proceso %d terminó debido a que recibió la señal %d**\n",pid,WTERMSIG(status));
			}
		}
	}

	printf("\n**Proceso %d termina**",getpid());
	return 0;
}
