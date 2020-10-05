#include <stdio.h>
#include <stdlib.h>
#include "../headers/tree.h"

#include <string.h>

int cant_nod = 0; // cantidad de variables insertada en la tabla de simbolos

 node* load_node( tree nd, tree ni, tree nn , nodoL* inf) {
 	node* n = malloc(sizeof(node));
 	n->hi = ni;
	n->hd = nd;
	n->hh = nn;
	n->info = inf;
	cant_nod++;
	return n;
 }
 

 int size() {
 	return cant_nod;
 }





