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

enum type_var_fun analyze_types(tree* t, int flag) {
	if(t->dato->flag==OP) {
		enum type_var_fun val_hi;
		enum type_var_fun val_hd;
		/*Asignacion*/
		if(strcmp(t->dato->op,"=")==0) {
			val_hi = analyze_types(t->hi, 0);
			val_hd = analyze_types(t->hd, 0);
			if(val_hi == val_hd) {
				return val_hi;
			}
			type_error("Type error: The variable must be the same type of expression\n");
		}
		/*Return*/
		if(strcmp(t->dato->op,"RETURN")==0) {
			if(!flag) {	
				has_return = 1;
			}
			if(function_return_type==VOID) {
				if(t->hi!=NULL) {
					type_error("Type error: return must be void\n");
				}
				return VOID;
			}
			else {
				if(t->hi == NULL || function_return_type!=analyze_types(t->hi, 0)) {
					type_error("Type error: wrong type in return\n");
				}
				return function_return_type;
			}
		}
		/*Operadores booleanos*/
		if(strcmp(t->dato->op,"!")==0) {
			if(analyze_types(t->hi, 0) != BOOL) {
				type_error("Type error: The ! operator needs a bool type\n");
			}
			t -> dato -> type = BOOL;
			return BOOL;
		}
		if(strcmp(t->dato->op,"&&")==0) {
			val_hi = analyze_types(t->hi, 0);
			val_hd = analyze_types(t->hd, 0);
			if(val_hi == BOOL && val_hd == BOOL) {
				t -> dato -> type = BOOL;
				return BOOL;
			}
			else {
				type_error("Type error: The && operator needs a bool type\n");
			}
		}
		if(strcmp(t->dato->op,"==")==0) {
			val_hi = analyze_types(t->hi, 0);
			val_hd = analyze_types(t->hd, 0);
			if(val_hi == val_hd) {
				t -> dato -> type = BOOL;
				return BOOL;
			}
			type_error("Type error: The two expressions in == must be the same type\n");
		}
		if(strcmp(t->dato->op,"<")==0) {
			val_hi = analyze_types(t->hi, 0);
			val_hd = analyze_types(t->hd, 0);
			if(val_hi == val_hd) {
				t -> dato -> type = BOOL;
				return BOOL;
			}
			type_error("Type error: The two expressions in < must be the same type\n");
		}
		/*Si se llego hasta aca, solo nos quedan operadores aritmeticos(+,-,*)*/
		val_hi = analyze_types(t->hi, 0);
		val_hd = analyze_types(t->hd, 0);
		if(val_hi == INT && val_hd == INT) {
			t -> dato -> type = INT;
			return INT;
		}
		type_error("Type error: The two expresions in arithmetic operations must be integer\n");
	}
	else {
		enum type_var_fun val_hi;
		if(t->dato->flag == STATEMENT) {
			/*If statement*/
			if(strcmp(t->dato->op,"IF")==0) {
				int unsecure_ret_then = 0;
				int unsecure_ret_else = 0;
				val_hi = analyze_types(t->hi, 0);
				if(val_hi == BOOL) {
					t -> dato -> type = BOOL;
					if(t -> hh != NULL) {
						analyze(t -> hh, 1);
						unsecure_ret_then = has_not_secure_return(t -> hh);
					}
					if(t -> hd != NULL){
						analyze(t -> hd, 1);
						unsecure_ret_else = has_not_secure_return(t -> hd);
					}
					if(unsecure_ret_then && unsecure_ret_else && !flag) {
						has_return = 1;
					}
					return BOOL;
				}
				type_error("Type error: The expression in a if statement must be BOOL\n");
			}
			if(strcmp(t->dato->op, "WHILE") == 0) {
				val_hi = analyze_types(t -> hi, 0);
				if(val_hi == BOOL) {
					t -> dato -> type = BOOL;
					if(t -> hh != NULL) {
						analyze(t -> hh, 1);
					}
				}
				else {
					type_error("Type error: The expression in a while statement must be BOOL\n");
				}
			}
		}
		else {
			return t -> dato -> type;
		}
	}
}

void analyze(tree* t, int flag) {
	if(strcmp(t->dato->op, ";") == 0 || strcmp(t->dato->op, "FUN") == 0) {
		if(t->hi != NULL) {
			analyze(t->hi, flag);
		}
		if(t->hh != NULL) {
			analyze(t->hh, flag);
		}
		if(t->hd != NULL) {
			analyze(t->hd, flag);
		}
	}
	else {
		analyze_types(t, flag);
	}
}

int has_not_secure_return(tree* t) {
	if(strcmp(t->dato->op, ";") == 0) {
		int ret = 0;
		if(t->hi != NULL) {
			ret = has_not_secure_return(t->hi);
			if(ret) {
				return 1;
			}
		}
		if(t->hh != NULL) {
			ret = has_not_secure_return(t->hh);
			if(ret) {
				return 1;
			}
		}
		if(t->hd != NULL) {
			ret = has_not_secure_return(t->hd);
			if(ret) {
				return 1;
			}
		}
		return ret;
	}
	else {
		if(strcmp(t->dato->op, "IF") == 0) {
			if(t ->  hi != NULL && t -> hd != NULL) {
				return has_not_secure_return(t -> hh) && has_not_secure_return(t -> hd);
			}
			return 0;
		}
		if(strcmp(t->dato->op,"RETURN")==0) {
			return 1;
		}
		return 0;
	}
}


void semantic_analyzer(dato* t) {
	function_return_type = t->type;
	tree* tr = t -> tree;
	has_return = 0;
	analyze(tr, 0);
	if(!has_return) {
		type_error("return statement not found.\n");
	}
}


