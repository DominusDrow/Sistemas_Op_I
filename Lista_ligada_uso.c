#include <stdio.h>
#include "Lista_ligada_circular.h"

int main(){
    insertarPrimero(100);
    insertarPrimero(45);
    insertarPrimero(12);
    insertarPrimero(4);
    printf("Luego de insertar 4 nodos al principio\n");
    imprimir();
    insertarUltimo(250);
    insertarUltimo(7);
    printf("Luego de insertar 2 nodos al final\n");
    imprimir();
    printf("Cantidad de nodos:%i\n", cantidad());
    printf("Luego de borrar el de la primer posicion:\n");
    borrar(1);
    imprimir();
    printf("Luego de borrar el de la cuarta posicion:\n");
    borrar(4);
    imprimir();
    liberar();
    
    return 0;
}

