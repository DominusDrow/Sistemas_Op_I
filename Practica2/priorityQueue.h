/**
 * PRACTICA 2: Simulador de algoritmo de planificación 
 * Round Robin con prioridades preventivo
 * 
 * INTEGRANTES:
 * Vásquez López Alfredo Omar    	201957903
 * Pazos Quezada Azarel          	201905195
 * Eusebio Aquino José Ángel 	 	201969852
 * Javier Olivares Héctor 		201938693
 * García Espinoza Alejandro Tonatiuh 	201910235
*/

/***SIMULADOR DE PLANIFICACIÓN A LARGO PLAZO***/

#include <stdlib.h>
#include <time.h>

#define QUANTUM 10

//Estructura del nodo 
struct node 
{
    int id;
    int priority;
    int tExe;
    int tArrival;
    int tWait;
    int tEnding;    
    int remainingTime;
    int remainingQuantum;
    struct node* next;
};

struct node* head = NULL;
struct node* current = NULL;

/**
 * Funcion que recibe  un nodo el cual lo ordena dentro de
 * la lista ligada sugun su prioridad en forma acendente.
 */
void push (struct node* process)
{
    if (head == NULL)
    {
        head = process;
        process->next = head;
    }
    else if (process->priority < head->priority)
    {
        if (head->next = head)
        {
            current = head;
            process->next = head;
            head = process;
            current->next = head;
        }
        else
        {
            current = head;
            while(current->next != head)
            {
                current = current->next;
            }
            process->next = head;
            head = process;
            current->next=head;
        }
    }
    else
    {
        struct node* current = head;

        while (process->priority > current->priority && current->next != head)
        {
            current = current->next;
        }
        
        process->next = current->next;
        current->next = process;
    }
}

void pushLast (struct node* process) {
    current = head;

    if (head == NULL)
    {
        head = process;
    }
    else
    {
        while (current->next != head)
        {
            current = current->next;
        }
        current->next = process;
        process->next = head;
    }
}

/**
 * Funcion que crea un nuevo nodo y lo retorna
 * en donde los primeros tres parametros (identificar, 
 * prioridad y tiempo de ejecucion) se igualan a los 
 * valores pasados por parametro.
 * 
 * Parametros:
 * int identificador, prioridad, tiempo de ejecucion
 */
void create(int id,int priority, int tExe){
    struct node* created = malloc(sizeof(struct node));
    created->id = id;
    created->priority = priority;
    created->tExe = tExe;
    created->next = NULL;
    created->remainingTime = tExe;
    created->remainingQuantum = QUANTUM;
    created->tArrival = time (NULL);
    push (created);
}

/**
 * Funcion que devuelve el nodo raiz que es el que
 * contiene el menor valor numerico en su campo "prioridad"
 * no recibe parametros.
 */
struct node* pop()
{
    return head;
}

//delete first item
struct node * deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   if(head->next == head) {  
      head = NULL;
      return tempLink;
   }     

    current = head;
    while (current->next != head)
    {
        current = current->next;
    }
    current->next = head->next;
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}


/**
 * Funcion que libera la memoria utilizada por la lista ligada 
 * creada en la ejecucion del programa una vez que este halla 
 * finalizado.
 */
void freeSpace()
{
   if (head != NULL)
   {
        struct node *delete;
        current = head->next;

        while (current != head)
        {
            delete = current;
            current = current->next;
            free (delete);
        }
        free (head);
    }
}
