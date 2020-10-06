#ifndef _STACK_H
#define _STACK_H
#include "structures.h"

void createStack(stack_node** p);

int isEmpty(struct stack_node* p) ;

void push(struct stack_node** p);

nodoL* pop(struct stack_node** p);

nodoL* peek(struct stack_node* p); 



#endif
