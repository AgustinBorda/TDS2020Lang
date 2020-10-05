

#ifndef _TABLE_C
#define _TABLE_C

#include <stdio.h>
#include <stdlib.h>
#include "../headers/table.h"

#include <string.h>

int cant_var = 0; // cantidad de variables insertada en la tabla de simbolos

/*int buscar_valor(nodoL* head, char* var) {
	nodoL* aux = head;
	while (aux != NULL ) {
		if (strcmp(aux -> info.name, var)==0) {		
		   return aux -> info.value; 
		}  
		aux = aux -> sig; 
	}
}*/


/* Retorna 1 si la variable existe en la TS, 0 en otro caso */
int existe(nodoL* head, char* var){
	nodoL* aux = head;
	while(aux != NULL) { 
		if (strcmp(aux->info.name, var)==0) {		
		   return 1; 
		}  
		aux = aux -> sig; 
	} 
	return 0;	
}

/* Inserta la variable con su valor en la TS */
/* Retorna 1 si pudo insertar correctamente, 0 si ya existe, -1 si la TS esta llena*/
int insertar(nodoL** head, dato d) {

	if (existe(*head, d.name) != 1) {
		nodoL* aux = malloc(sizeof(nodoL)); //Crear un nuevo nodo.
		aux -> flag = nodoL -> flag;
		aux -> info.name = d.name;
		aux -> info.type = d.type;
		if (aux -> flag == VAR) {
			aux -> info.value = d.value;
		} else {
			aux -> info.sig = d.sig;
		}
		cant_var++;
		(*aux).sig = *head; //Apuntar el nodo al nodo que apuntaba la lista.
		*head = aux; //Hacer que la lista apunte al nodo nuevo.

	    return 1; // se inserto correctamente 
	} else  {  
	    return 0; // ya existe, no se inserta
	}
	
}

void borrar(nodoL** head, char* var){
    nodoL* aux = *head; //puntero auxiliar al primer nodoi
    nodoL* aux2 = NULL;
    while (aux != NULL && strcmp(aux->info.name, var)!=0){
	aux2 = aux;
    	aux = aux->sig;	
    }
    if(aux !=NULL && strcmp(aux->info.name, var)==0) {
	if(aux2 ==NULL) {
		*head = aux->sig;
	}
	else {
        	aux2->sig = aux->sig;
	        free(aux);

	}
    }
}


int mostrar(nodoL* head) {
	//Crea y asigna 0 a la variable a devolver
	//Preguntar si la lista no es vacia
	if (head != NULL){
		//Asigna 1 a la variable i.
		//Muestra el valor actual en pantalla
		printf(" |%s =",head->info.name);
		printf(" %d|->",head->info.type);
		//Llama la función con el próximo valor.																																		
		mostrar(head -> sig);
	}
	else {
		printf(" NULL\n");
	}
	return 0;
}


#endif
