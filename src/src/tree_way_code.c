#include <stdio.h>
#include <stdlib.h>
#include "../headers/tree_way_code.h"
#include "../headers/table.h"



int write_three_code(dato* t, list* l) {
	tree* tr = t -> tree;
	three_address_code* tac = malloc(sizeof(three_address_code));
	tac -> opcode = INIT_FUN;
	tac -> op1 = tr;
	last_insert(l, tac);
	analyze2(tr, l);
	tac = malloc(sizeof(three_address_code));
	tac -> opcode = END_FUN;
	tac -> op1 = tr;
	last_insert(l, tac);
	return 0;
}

void analyze2(tree* t, list* l) {
	if(strcmp(t->dato->op, ";") == 0 || strcmp(t->dato->op, "FUN") == 0) {
		if(t->hi != NULL) {
			analyze(t->hi, l);
		}
		if(t->hh != NULL) {
			analyze(t->hh, l);
		}
		if(t->hd != NULL) {
			analyze(t->hd, l);
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

void tac_op(three_address_code* tac, tree* t){
	tac -> dest = t->dato;
	tac -> op1 = t->hi;
	tac -> op2 = t->hd;
}

dato_tree* writeOp(tree* root, list* l) {
	dato_tree* val_hi;
	dato_tree* val_hd;
	if(root -> hi != NULL) {
		val_hi = write(root->hi, l);
	}
	if(root -> hd != NULL) {
		val_hd = write(root->hd, l);
	}
	three_address_code* tac = malloc(sizeof(three_address_code));
	if(strcmp(root->dato->op, "+") == 0) {
		tac -> opcode = ADD;
		tac_op(tac, root);
		last_insert(l, tac);
	}
	if(strcmp(root->dato->op, "-") == 0) {
		tac -> opcode = SUB;
		tac_op(tac, root);
		last_insert(l, tac);
	}
	if(strcmp(root->dato->op, "*") == 0) {
		tac -> opcode = MULT;
		tac_op(tac, root);
		last_insert(l, tac);
	}
	if(strcmp(root->dato->op, "&&") == 0) {
		tac -> opcode = AND;
		tac_op(tac, root);
		last_insert(l, tac);
		
	}
	if(strcmp(root->dato->op, "=") == 0) {
		tac -> opcode = ASSIGN;
		tac_op(tac, root);
		last_insert(l, tac);
	}
	if(strcmp(root->dato->op, "!") == 0) {
		tac -> opcode = NOT;
		//TODO

	}
	if(strcmp(root->dato->op, "RETURN") == 0) {
		tac -> opcode = RET;
		printf("hubo un error");
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

