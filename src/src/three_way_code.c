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
	if(val_hi != NULL) {
		tac -> op1 = val_hi;
	}
	if(val_hd != NULL) {
		tac -> op2 = val_hd;
	}
	if(root -> dato != NULL) {
		root -> dato -> temp_name = genTemp();
	}
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
		tac -> op1 = val_hd;
		tac -> op2 = NULL;
		tac -> dest = val_hi;

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
	if(strcmp(root->dato->op, "<") == 0) {
		tac -> opcode = MINOR;
	}
	if(tac -> dest == NULL) {
		tac -> dest = root -> dato;
	}
	last_insert(l, tac);
	return root -> dato;
}

void write_statement(tree* root, list* l) {
	if(strcmp(root->dato->op, "IF")==0) {
 		dato_tree* val_exp = write(root -> hi, l);
		three_address_code* tac_if = malloc(sizeof(three_address_code));
		dato_tree* label_else = malloc(sizeof(dato_tree));
		label_else -> temp_name = genTemp();
		label_else -> flag = LABEL_NAME;
		tac_if -> opcode = IF_FALSE;
		tac_if -> op1 = val_exp;
		tac_if -> op2 = label_else;
		last_insert(l, tac_if);
		if (root -> hh != NULL) {
			write(root -> hh, l);
		}
		if(root -> hd != NULL) {
			dato_tree* label_end = malloc(sizeof(dato_tree));
			label_end -> temp_name = genTemp();
			label_end -> flag = LABEL_NAME;
			three_address_code* jump_end = malloc(sizeof(three_address_code));
			jump_end -> op1 = label_end;
			jump_end -> opcode = JUMP;
			last_insert(l, jump_end);
			three_address_code* tac_else = malloc(sizeof(three_address_code));
			tac_else -> op1 = label_else;
			tac_else -> opcode = LABEL;
			last_insert(l, tac_else);
			write(root -> hd, l);
			three_address_code* tac_end = malloc(sizeof(three_address_code));
			tac_end -> opcode = LABEL;
			tac_end -> op1 = label_end;
			last_insert(l, tac_end);
		}
		else {
			three_address_code* tac_else = malloc(sizeof(three_address_code));
			tac_else -> op1 = label_else;
			tac_else -> opcode = LABEL;
			last_insert(l, tac_else);
		}
	}
	if(strcmp(root->dato->op, "WHILE")==0) {
 		dato_tree* val_exp = write(root -> hi, l);
		three_address_code* tac_while = malloc(sizeof(three_address_code));
		dato_tree* label_inic = malloc(sizeof(dato_tree));
		label_inic -> temp_name = genTemp();
		label_inic -> flag = LABEL_NAME;
		tac_while -> opcode = IF_FALSE;
		tac_while -> op1 = val_exp;
		tac_while -> op2 = label_inic;
		last_insert(l, tac_while);
		if (root -> hh != NULL) {
			dato_tree* label_while = malloc(sizeof(dato_tree));
			label_while -> temp_name = genTemp();
			label_while -> flag = LABEL_NAME;
			three_address_code* jump_inic = malloc(sizeof(three_address_code));
			jump_inic -> op1 = label_while;
			jump_inic -> opcode = JUMP;
			last_insert(l, jump_inic);
		}
 }


dato_tree* write(tree* root, list* l) {
        switch(root->dato->flag) {
		case 0 : return writeId(root);
			 break;
		case 1 : return writeConst(root);
			 break;
		case 2 : return writeOp(root,l);
			 break;
		case 3 : write_statement(root, l);
			 return NULL; //peligroso
			 break;
		default : exit(1);
			  break;
	}
}

