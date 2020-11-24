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

char* get_tac_opcode(op_twc o) {
	switch (o) {
		case 0: return "ASSIGN";
		case 1: return "ADD";
		case 2: return "SUB";
		case 3: return "MULT";
		case 4: return "AND";
		case 5: return "NOT";
		case 6: return "RET";
		case 7: return "INIT_FUN";
		case 8: return "END_FUN";
		case 9: return "EQ";
		case 10: return "MINOR";
		case 11: return "JUMP";
		case 12: return "LABEL";
		case 13: return "IF_FALSE";
		case 14: return "IF_TRUE";
		defaul: return "CALL";
	}
}

void show_tac(list* head) {
	nodoL* aux = head -> list -> sig;
	while(aux != NULL) {
		three_address_code* ptr1 = aux -> info;
		printf("%s ", get_tac_opcode(ptr1-> opcode));
		if (ptr1 -> dest != NULL) {
			switch (ptr1->dest->flag) {
				case 0 : printf("%s ",ptr1->dest->data->name);
						break;
				case 1 : printf("%d ",ptr1->dest->value);
						break;
				default : printf("%s ", ptr1->dest->temp_name);
						break;				
			}
		}
		if(ptr1->op1 != NULL) {
			switch (ptr1->op1->flag) {
				case 0 : printf("%s ",ptr1->op1->data->name);
						break;
				case 1 : printf("%d ",ptr1->op1->value);
						break;
				default : printf("%s ", ptr1->op1->temp_name);
						break;				
			}
		}
		if(ptr1->op2 != NULL) {
			switch (ptr1->op2->flag) {
				case 0 : printf("%s",ptr1->op2->data->name);
						break;
				case 1 : printf("%d",ptr1->op2->value);
						break;
				default : printf("%s", ptr1->op2->temp_name);
						break;				
			}
		}
		printf("\n");
		aux = aux -> sig;
	}
}


void empty_list(list** head) {
	nodoL* aux = (*head) -> list;
	free(*head);
	nodoL* aux2; 
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

int last_insert(list* head, void* d){
	nodoL* aux = head -> list;
	while(aux->sig != NULL) {
		aux = aux -> sig;
	}
	nodoL* aux2 = malloc(sizeof(nodoL));
	aux2 -> info = d;
	aux2 -> sig = NULL;
	aux -> sig = aux2;
	head -> size++;
	return 1;
}
