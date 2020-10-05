#ifndef _STACK_H
#define _STACK_H
#include "structures.h"

struct stack_node* createStack() ;

int isEmpty(struct stack_node* p) ;

void push(struct stack_node** p, nodoL* list);

nodoL* pop(struct stack_node* p);

nodoL* peek(struct stack_node* p); 



#endif
