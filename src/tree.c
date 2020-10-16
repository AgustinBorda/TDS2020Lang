#include <stdio.h>
#include <stdlib.h>
#include "../headers/tree.h"

#include <string.h>


tree* load_node( tree* nd, tree* ni, tree* nn , dato_tree* inf) {
 	tree* n = malloc(sizeof(tree));
 	n->hi = ni;
	n->hd = nd;
	n->hh = nn;
	n->dato = inf;
	return n;
 }
 





