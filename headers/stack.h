#ifndef _STACK_H
#define _STACK_H
#include "structures.h"

struct stack_node* createStack() ;

int isEmpty(struct stack_node* p) ;

void push(struct stack_node* p, nodoL list);

int pop(struct stack_node* p);

int peek(struct stack_node* p); 



#endif