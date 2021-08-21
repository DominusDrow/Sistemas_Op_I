/**
 * PRACTICA 1: Listas ligadas circulares y archivos
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar           201957903
 * Javier Olivares Héctor               201937593
 * Pazos Quezada Azarel                 201905195
 * Eusebio Aquino José Ángel            201969852
 * García Espinoza Alejandro Tonatiuh   201910235
*/

#include <stdio.h>
#include "Lista_ligada_circular.h"

#include <stdio.h>

void readFile(const char* filename);
void writeFile(const char*filename, nodo root);

void readFile (const char* filename)
{
	FILE* file = fopen (filename, "r");
	int i = 0;

	fscanf (file, "%d", &i);
	while (!feof (file))
	{
		insertar (tamanio () + 1, i);	
		fscanf (file, "%d", &i);
	}

	fclose (file);
}

void writeFile (const char* filename, nodo root)
{
	FILE* file = fopen (filename, "w");
	nodo aux = root;
	int i;

	if (file != NULL)
	{
		while (aux != NULL && aux->sig != root)
		{
			i = aux->num;
			fprintf (file, "%d\n", i);
			aux = aux->sig;
		}
		if (aux != NULL)
		{
			i = aux->num;
			fprintf (file, "%d\n", i);
		}
	}
	fclose (file);
}

int menu()
{
    int opc;
    printf("\nLista Circular\n");
    printf("[1] Insertar desde archivo\n");
    printf("[2] Insertar en posición i\n");
    printf("[3] Eliminar un dato\n");
    printf("[4] Buscar un dato\n");
    printf("[6] Salir\n");
    scanf("%d", &opc);
    return opc;
}

int main()
{
    int opc=menu(), dato, posicion;

    while(opc!=6)
    {
        switch (opc)
        {
        case 1:
            readFile("test.txt");
            break;
        case 2:
            printf("\nDame un numero a insertar en la lista ");
            scanf("%d", &dato);
            printf("\n¿En que posicion deseas insertar el numero? ");
            scanf("%d", &posicion);
            insertar(posicion,dato);
            break;
        case 3:
            printf("\nDame la posicion en las lista del numero a eliminar ");
            scanf("%d", &posicion);
            eliminar(posicion);
            break;
        case 4:
            printf("\n¿Que numero deseas buscar? ");
            scanf("%d", &dato);
            buscar(dato);
            break;
        default:
            printf("\nError: Opcion no valida ");
            break;
        }
        if(!vacia())
        {
            printf("\t\t\nLista");
            imprimir();
        }
        opc=menu();
    }
    
    return 0;
}

