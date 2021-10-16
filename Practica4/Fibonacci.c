/**
 * PRACTICA 4: Simulador de shell con fork() y exec()
 * 
 * INTEGRANTES:
 * Eusebio Aquino Jose Angel 	 	    201969852
 * Vasquez Lopez Alfredo Omar    	    201957903
 * Pazos Quezada Azarel          	    201905195
 * Javier Olivares Hector 		        201938693
 * Garcia Espinoza Alejandro Tonatiuh 	201910235
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Fibonacci(int n){
	if (n < 2)
		return 1;
	else
		return Fibonacci(n-1) + Fibonacci(n-2);
}

int main(int argc, char *argv[]){
	
	int cont, i;
	cont = atoi(argv[1]);

	// Funcion Fibonacci
	for(i=0; i<cont; i++){
		if(i<(cont-1)){
			printf("%i, ",Fibonacci(i));
		}else{
			printf("%i",Fibonacci(i));
		}
	}
	printf("\n");

	return 0;
}
