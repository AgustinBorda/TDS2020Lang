#include <stdio.h>
#include <stdlib.h>
#include "../headers/table.h"

#include <string.h>
//TODO: Utilizar un elem. ficticio
//sino perdemos las referencias

void create_list(nodoL** p) {
	(*p) = malloc(sizeof(nodoL));
	(*p) -> sig = NULL;
	return;
}

int exist(nodoL* head, char* var) {
	nodoL* aux = head -> sig;
	while(aux != NULL) {
		if(strcmp(var,aux->info.name) == 0) {
			return 1;
		}
		aux = aux -> sig;
	}
	return 0;
}

int insert(nodoL* head, dato d) {
	if(!exist(head, d.name)) {
		nodoL* aux = malloc(sizeof(nodoL));
		aux -> info = d;
		aux -> sig = head -> sig;
		head ->sig = aux;
		return 1;
	}
	return 0;
}

void show(nodoL* head) {
	nodoL* aux = head -> sig;
	while(aux != NULL) {
		printf("Type: %d\nName: %s\nValue: %i\nV\n",aux->info.type,aux->info.name,aux->info.value);
		aux = aux -> sig;
	}
}

int delete_node(nodoL* head, char* var) {
	nodoL* aux = head;
	while(aux->sig!=NULL) {
		if(strcmp(var,aux->sig->info.name)==0) {
			nodoL* aux2 = aux ->sig;
			aux -> sig = aux2 -> sig;
			free(aux2);
			return 1;
		}
		aux = aux -> sig;
	}
	return 0;
}



