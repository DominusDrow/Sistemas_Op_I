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
#include <math.h>

void VerificaNumero(double n){
	if((n - (int)n)>1){
		printf("%.3lf\n",n);	
	}else{
		printf("%f\n",n);	
	}
}

int main(int argc, char *argv[]){
	
	double x1, x2;
	double a, b, c;
	
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
		
	// Ecuacion Cuadratica
	if (a == 0){
        printf("El coeficiente a no puede ser igual a cero");
	}else {
        double discriminante = pow(b, 2) - 4 * a*c;
        if (discriminante >= 0)
            if (discriminante == 0) {
                double x = -b / (2 * a);
                printf("La raíz única es %.3lf\n", x);
            } else {
                double x1, x2;
                x1 = (-b + sqrt(discriminante)) / (2 * a);
                x2 = (-b - sqrt(discriminante)) / (2 * a);
                printf("La raíz real x1 es %.3lf\n", x1);
                printf("La raíz real x2 es %.3lf\n", x2);
            }
        else {
            double parteReal, parteImaginaria;
            discriminante = fabs(discriminante);
            parteReal = -b / (2 * a);
            parteImaginaria = sqrt(discriminante) / (2 * a);
            printf("La raíz compleja x1 es %.3lf + %.3lfi\n", parteReal, parteImaginaria);
            printf("La raíz compleja x2 es %.3lf - %.3lfi\n", parteReal, parteImaginaria);
        }
    }
	
			
	return 0;
}
