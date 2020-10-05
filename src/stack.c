#include <stdlib.h>
#include "../headers/stack.h"

struct stack_node* createStack() {
	stack_node* pila = malloc(sizeof(stack_node));
	pila -> level = 0;
	pila -> sig = NULL;
	return pila;
}

int isEmpty(struct stack_node* p) {
	if(p -> level < 1) return 1;
	return 0; 
}

void push(struct stack_node** p, nodoL* list) {
		stack_node* p2 = malloc(sizeof(stack_node));
		p2 -> level = (*p) -> level + 1; 
		p2 -> list = list; 
		(*p2).sig = *p; 
		*p = p2;
}

nodoL* pop(struct stack_node* p) {
	stack_node* p2 = p;
	p = p -> sig;
	nodoL* ret_val = p2->list;
	free(p2);
	return ret_val;
}

nodoL* peek(struct stack_node* p) {
	return p -> list;
}

