#include <stdio.h>
#include <stdlib.h>
#include "../headers/tree.h"

#include <string.h>


tree* load_node( tree* hi, tree* hh, tree* hd , dato_tree* inf) {
 	tree* n = malloc(sizeof(tree));
 	n->hi = hi;
	n->hd = hd;
	n->hh = hh;
	n->dato = inf;
	return n;
 }
 





