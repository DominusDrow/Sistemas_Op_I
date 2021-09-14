#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int tiempoEspera = 0, time=0;
	int nProcesosRestantes = 10;
	//PROCESO* raiz = NULL;

	for (time = 0; nProcesosRestantes != 0; time++)
	{
		if (tiempoEspera == 0)
		{
			//leerLote(5, raiz);
				printf ("lectura\n");
			tiempoEspera = 3;
		}

		// Buscar proceso con mayor prioridad
		// Almacenar quantum restante del proceso
		// proceso.tiempo_restante--;
		// Si el tiempo restante del proceso es == 0
		// nProcesosRestantes--
		// Eliminar el proceso de la lista ligada/cola


		nProcesosRestantes--;
		tiempoEspera--;
		printf ("1 de quantum\n");
		// Dormir 1 segundo
		sleep (1);
	}

}
