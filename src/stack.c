#include <stdlib.h>
#include "../headers/stack.h"
#include "../headers/table.h"

void createStack(stack_node** p) {
	nodoL* list = NULL;
	create_list(&list);
	(*p) = malloc(sizeof(stack_node));
	(*p) -> level = 0;
	(*p) -> sig = NULL;
	(*p) -> list = list; 
	return;
}

int isEmpty(struct stack_node* p) {
	if(p -> level < 1) return 1;
	return 0; 
}

void push(struct stack_node** p) {
		nodoL* list = NULL;
		create_list(&list);
		stack_node* p2 = malloc(sizeof(stack_node));
		p2 -> level = (*p) -> level + 1; 
		p2 -> list = list; 
		(*p2).sig = *p; 
		*p = p2;
}

nodoL* pop(struct stack_node** p) {
	stack_node* p2 = *p;
	*p = (*p) -> sig;
	nodoL* ret_val = p2->list;
	free(p2);
	return ret_val;
}

nodoL* peek(struct stack_node* p) {
	return p -> list;
}

