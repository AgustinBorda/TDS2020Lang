#ifndef _TREE_H
#define _TREE_H

#include "structures.h"

typedef node* tree;

/*
*Construye un nodo del tipo tree y lo carga
*/

 node* load_node( tree nd, tree ni, tree nn , nodoL* inf);

 node* load_node( tree nd, tree ni, tree nn , int constante);

int size();


#endif
