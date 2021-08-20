/**
 * PRACTICA 1: Listas ligadas circulares y archivos
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    201957903
 * 
*/

#include <stdio.h> 
#include <stdlib.h>

//Estructura del nodo 
struct Nodo {
    int info;
    struct Nodo *sig;
    struct Nodo *ant;
};

//Renombrar un puntero a la estructura nodo
typedef struct Nodo* nodo;

//Creacion de la lista ligada circular
nodo raiz=NULL;

/*
 * Funcion que libera la memoria utilizada en la ejecucion
 * del programa una vez que este halla finalizado.
 */
void liberar()
{
   if (raiz != NULL) {
        nodo reco = raiz->sig;
        nodo bor;
        while (reco != raiz)
        {
            bor = reco;
            reco = reco->sig;
            free(bor);
        }
        free(raiz);
    }
}

int vacia()
{
    if (raiz == NULL)   return 1;
    else    return 0;
        
}


void insertarPrimero(int x)
{
    nodo nuevo;
    nuevo=malloc(sizeof(struct Nodo));
    nuevo->info = x;
    if (raiz == NULL)
    {
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        raiz = nuevo;
    }
    else
    {
        nodo ultimo = raiz->ant;
        nuevo->sig = raiz;
        nuevo->ant = ultimo;
        raiz->ant = nuevo;
        ultimo->sig = nuevo;
        raiz = nuevo;
    }
}

void insertarUltimo(int x)
{
    nodo nuevo;
    nuevo=malloc(sizeof(struct Nodo));
    nuevo->info = x;
    if (raiz == NULL)
    {
        nuevo->sig = nuevo;
        nuevo->ant = nuevo;
        raiz = nuevo;
    }
    else
    {
        nodo ultimo = raiz->ant;
        nuevo->sig = raiz;
        nuevo->ant = ultimo;
        raiz->ant = nuevo;
        ultimo->sig = nuevo;
    }
}

void imprimir()
{
    if (!vacia()) {
        nodo reco = raiz;
        do {
            printf("%i ",reco->info);
            reco = reco->sig;
        } while (reco != raiz);
        printf("\n");
    }
}

int cantidad()
{
    int cant = 0;
    if (!vacia())
    {
        nodo reco = raiz;
        do {
            cant++;
            reco = reco->sig;
        } while (reco != raiz);
    }
    return cant;
}

void borrar(int pos)
{
    if (pos <= cantidad())
    {
        if (pos == 1)
        {
            if (cantidad() == 1)
            {
                free(raiz);
                raiz = NULL;
            }
            else
            {
                nodo bor = raiz;
                nodo ultimo = raiz->ant;
                raiz = raiz->sig;
                ultimo->sig = raiz;
                raiz->ant = ultimo;
                free(bor);
            }
        }
        else {
            nodo reco = raiz;
            int f;
            for (f = 1; f <= pos - 1; f++)
                reco = reco->sig;
            nodo bor = reco;
            nodo anterior = reco->ant;
            reco = reco->sig;
            anterior->sig = reco;
            reco->ant = anterior;
            free(bor);
        }
    }
}
