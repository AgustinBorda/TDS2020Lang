#include <stdlib.h>
#include "../headers/stack.h"
#include "../headers/table.h"
#include <stdio.h>

void createStack(stack_node** p) {
	list* list = NULL;
	create_list(&list,SYMBOL);
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
		list* list = NULL;
		create_list(&list,SYMBOL);
		stack_node* p2 = malloc(sizeof(stack_node));
		p2 -> level = (*p) -> level + 1; 
		p2 -> list = list; 
		(*p2).sig = *p; 
		*p = p2;
}

void pop(struct stack_node** p) {
	stack_node* p2 = *p;
	*p = (*p) -> sig;
	empty_list(&(p2->list));
	free(p2);
}

list* peek(struct stack_node* p) {
	return p -> list;
}


