#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/three_way_code.h"
#include "../headers/table.h"
#include "../headers/tempGen.h"



int write_three_code(dato* t, list* l) {
	tree* tr = t -> tree;
	three_address_code* tac = malloc(sizeof(three_address_code));
	tac -> opcode = INIT_FUN;
	tr -> dato -> temp_name = tr -> dato -> data -> name;
	tac -> op1 = tr -> dato;
	last_insert(l, tac);
	analyze_tac(tr, l);
	tac = malloc(sizeof(three_address_code));
	tac -> opcode = END_FUN;
	tac -> op1 = tr -> dato;
	last_insert(l, tac);
	return 0;
}

void analyze_tac(tree* t, list* l) {
	if(strcmp(t->dato->op, ";") == 0 || strcmp(t->dato->op, "FUN") == 0) {
		if(t->hi != NULL) {
			analyze_tac(t->hi, l);
		}
		if(t->hh != NULL) {
			analyze_tac(t->hh, l);
		}
		if(t->hd != NULL) {
			analyze_tac(t->hd, l);
		}
	}
	else {
		write(t, l);
	}
}

dato_tree* writeConst(tree* root) {
		return root -> dato;
}

dato_tree* writeId(tree* root) {
	return root -> dato;
}

dato_tree* writeOp(tree* root, list* l) {
	dato_tree* val_hi = NULL;
	dato_tree* val_hd = NULL;
	if(root -> hi != NULL) {
		val_hi = write(root->hi, l);
	}
	if(root -> hd != NULL) {
		val_hd = write(root->hd, l);
	}
	three_address_code* tac = malloc(sizeof(three_address_code));
	if(strcmp(root->dato->op, "+") == 0) {
		tac -> opcode = ADD;
	}
	if(strcmp(root->dato->op, "-") == 0) {
	tac -> opcode = SUB;
	}
	if(strcmp(root->dato->op, "*") == 0) {
		tac -> opcode = MULT;
	}
	if(strcmp(root->dato->op, "&&") == 0) {
		tac -> opcode = AND;
		
	}
	if(strcmp(root->dato->op, "=") == 0) {
		tac -> opcode = ASSIGN;
	}
	if(strcmp(root->dato->op, "!") == 0) {
		tac -> opcode = NOT;

	}
	if(strcmp(root->dato->op, "RETURN") == 0) {
		tac -> opcode = RET;
	}
	if(strcmp(root->dato->op, "==") == 0) {
		tac -> opcode = EQ;
	}
	if(val_hi != NULL) {
		tac -> op1 = val_hi;
	}
	if(val_hd != NULL) {
		tac -> op2 = val_hd;
	}
	if(root -> dato != NULL) {
		root -> dato -> temp_name = genTemp();
	}
	tac -> dest = root -> dato;
	last_insert(l, tac);
	return root -> dato;
}

dato_tree* write(tree* root, list* l) {
        switch(root->dato->flag) {
		case 0 : return writeId(root);
			 break;
		case 1 : return writeConst(root);
			 break;
		case 2 : return writeOp(root,l);
			 break;
		default : exit(1);
			  break;
	}
}

