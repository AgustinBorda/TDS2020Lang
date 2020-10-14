#include <stdio.h>
#include <stdlib.h>
#include "../headers/table.h"

#include <string.h>

void create_list(list** p, type_list type) {
	(*p) = malloc(sizeof(list));
	(*p) -> type = type;
	(*p) -> list = malloc(sizeof(nodoL));
	(*p) -> list -> sig = NULL;
	(*p) -> size = 0;
	return;
}


int exist(list* l, char* var) {
	nodoL* aux = l -> list -> sig;
	while(aux != NULL) {
		info_type* ptr = aux->info;
		if(strcmp(var,ptr -> name) == 0) {
			return 1;
		}
		aux = aux -> sig;
	}
	return 0;
}

int insert(list* head, void* d) {
	if(head -> type == 0 || head -> type == 1) {
		/*La tabla de simbolos o una lista de parametros, no queremos repetidos*/
		info_type* ptr = d;
		if(!exist(head, ptr->name)) {
			nodoL* aux = malloc(sizeof(nodoL));
			aux -> info = d;
			aux -> sig = head-> list -> sig;
			head -> list -> sig = aux;
			head -> size++;
			return 1;
		}
		return 0;
	}
	else { /*si es una lista de arboles, puede haber repetidos*/
		nodoL* aux = malloc(sizeof(nodoL));
		aux -> info = d;
		aux -> sig = head -> list -> sig;
		head -> list-> sig = aux;
		head -> size++;
		return 1;
	}
}

void* seek(list* head, char* var) {
	nodoL* aux = head -> list -> sig;
	while(aux != NULL) {
		info_type* ptr = aux->info;
		if(strcmp(var,ptr -> name) == 0) {
			return aux -> info;
		}
		aux = aux -> sig;
	}
	return NULL;
}

void show(list* head) {
	nodoL* aux = head -> list -> sig;
	while(aux != NULL) {
		info_type* ptr1 = aux -> info;
		printf("Type: %d\nName: %s\n",ptr1 ->type,ptr1->name);
		aux = aux -> sig;
	}
}



void empty_list(list** head) {
	nodoL* aux = (*head) -> list;
	*head = NULL;
	nodoL* aux2;
	(*head) -> size = 0; 
	while(aux != NULL) {
		aux2 = aux;
		aux = aux->sig;
		free(aux2);
	}
}

void* get(list* head, int i) {
	nodoL* aux = head -> list -> sig;
	int index = 0;
	while(index < i && aux != NULL) {
		aux = aux -> sig;
		index++;
	}
	if(aux == NULL)
		return NULL;
	return aux -> info;
}


int size(list* head) {
	return head -> size;
}

