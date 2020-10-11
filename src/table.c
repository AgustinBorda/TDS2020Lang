#include <stdio.h>
#include <stdlib.h>
#include "../headers/table.h"

#include <string.h>

void create_list(list** p, type_list type) {
	(*p) = malloc(sizeof(list));
	(*p) -> type = type;
	(*p) -> list = malloc(sizeof(nodoL))
	(*p) -> list -> sig = NULL;
	return;
}

//TODO: implementar desde aca (pasar todo a terminos de list)

int exist(list* l, char* var) {
	nodoL* aux = l -> list -> sig;
	while(aux != NULL) {
		if(strcmp(var,aux->info->name) == 0) {
			return 1;
		}
		aux = aux -> sig;
	}
	return 0;
}

int insert(nodoL* head, void* d) {
	if(!exist(head, d->name)) {
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
		printf("Type: %d\nName: %s\nValue: %i\nV\n",aux->info->type,aux->info->name,aux->info->value);
		aux = aux -> sig;
	}
}

int delete_node(nodoL* head, char* var) {
	nodoL* aux = head;
	while(aux->sig!=NULL) {
		if(strcmp(var,aux->sig->info->name)==0) {
			nodoL* aux2 = aux ->sig;
			aux -> sig = aux2 -> sig;
			free(aux2);
			return 1;
		}
		aux = aux -> sig;
	}
	return 0;
}

void empty_list(nodoL** head) {
	nodoL* aux = *head;
	*head = NULL;
	nodoL* aux2;
	while(aux != NULL) {
		aux2 = aux;
		aux = aux->sig;
		free(aux2);
	}
}
