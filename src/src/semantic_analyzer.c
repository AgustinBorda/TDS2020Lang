#include "../headers/semantic_analyzer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int has_return;
enum type_var_fun function_return_type;

void type_error(char* msg) {
	printf("%s",msg);
	exit(1);
}

enum type_var_fun analyze_types(tree* t) {
	if(t->dato->flag==OP) {
		enum type_var_fun val_hi;
		enum type_var_fun val_hd;
		/*Asignacion*/
		if(strcmp(t->dato->op,"=")==0) {
			val_hi = analyze_types(t->hi);
			val_hd = analyze_types(t->hd);;
			if(val_hi == val_hd) {
				return val_hi;
			}
			type_error("Type error: The variable must be the same type of expression\n");
		}
		/*Return*/
		if(strcmp(t->dato->op,"RETURN")==0) {
			has_return = 1;
			if(function_return_type==VOID) {
				if(t->hi!=NULL) {
					type_error("Type error: return must be void\n");
				}
				return VOID;
			}
			else {
				if(t->hi == NULL || function_return_type!=analyze_types(t->hi)) {
					type_error("Type error: wrong type in return\n");
				}
				return function_return_type;
			}
		}
		/*Operadores booleanos*/
		if(strcmp(t->dato->op,"!")==0) {
			if(analyze_types(t->hi) != BOOL) {
				type_error("Type error: The ! operator needs a bool type\n");
			}
			return BOOL;
		}
		if(strcmp(t->dato->op,"&&")==0) {
			val_hi = analyze_types(t->hi);
			val_hd = analyze_types(t->hd);
			if(val_hi == BOOL && val_hd == BOOL) {
				return BOOL;
			}
			else {
				type_error("Type error: The && operator needs a bool type\n");
			}
		}
		if(strcmp(t->dato->op,"==")==0) {
			val_hi = analyze_types(t->hi);
			val_hd = analyze_types(t->hd);
			if(val_hi == val_hd) {
				return BOOL;
			}
			type_error("Type error: The two expressions in == must be the same type\n");
		}
		/*Si se llego hasta aca, solo nos quedan operadores aritmeticos(+,-,*)*/
		val_hi = analyze_types(t->hi);
		val_hd = analyze_types(t->hd);
		if(val_hi == INT && val_hd == INT) {
			return INT;
		}
		type_error("Type error: The two expresions in arithmetic operations must be integer\n");
	}
	else {
		return t -> dato -> type;
	}
}

void analyze(tree* t) {
		if(strcmp(t->dato->op, ";") == 0 || strcmp(t->dato->op, "FUN") == 0) {
			if(t->hi != NULL) {
				analyze(t->hi);
			}
			if(t->hh != NULL) {
				analyze(t->hh);
			}
			if(t->hd != NULL) {
				analyze(t->hd);
			}
		}
		else {
			analyze_types(t);
		}
}


void semantic_analyzer(dato* t) {
	function_return_type = t->type;
	tree* tr = t -> tree;
	has_return = 0;
	analyze(tr);
	if(!has_return) {
		type_error("return statement not found.\n");
	}
}


