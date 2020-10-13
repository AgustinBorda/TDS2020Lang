#include <stdio.h>
#include <stdlib.h>
#include "../headers/table.h"

#include <string.h>

void create_list(list** p, type_list type) {
	(*p) = malloc(sizeof(list));
	(*p) -> type = type;
	(*p) -> list = malloc(sizeof(nodoL));
	(*p) -> list -> sig = NULL;
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
			return 1;
		}
		return 0;
	}
	else { /*si es una lista de arboles, puede haber repetidos*/
		nodoL* aux = malloc(sizeof(nodoL));
		aux -> info = d;
		aux -> sig = head -> list -> sig;
		head -> list-> sig = aux;
		return 1;
	}
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
	while(aux != NULL) {
		aux2 = aux;
		aux = aux->sig;
		free(aux2);
	}
}

int main() {
	list* symbol;
	list* params;
	create_list(&symbol,SYMBOL);
	create_list(&params,PARAM);
	dato* d1 = malloc(sizeof(dato));
	d1 -> type = 0;
	d1 -> name = "var1";
	insert(symbol,d1);
	dato* d2 = malloc(sizeof(dato));
	d2 -> type = 0;
	d2 -> name = "var2";
	insert(symbol,d2);
	info_type* p1 = malloc(sizeof(info_type));
	info_type* p2 = malloc(sizeof(info_type));
	p1 -> type = 0;
	p1 -> name = "param1";
	p2 -> type = 0;
	p2 -> name = "param2";
	insert(params,p1);
	insert(params,p2);
	printf("Simbolos: \n");
	show(symbol);
	printf("\n");
	printf("Parametros: \n");
	show(params);
	printf("\n");

}
