#ifndef _3_ADDRESS_CODE_H
#define _3_ADDRESS_CODE_H
#include "structures.h"
#include <stdio.h>


int write_three_code(dato* t, list* l);

void analyze_tac(tree* t, list* l);



dato_tree* writeConst(tree* root); 


dato_tree* writeId(tree* root);

void tac_op(three_address_code* tac, tree* t);


dato_tree* writeOp(tree* root, list* l);


dato_tree* write(tree* root, list* l);


#endif
