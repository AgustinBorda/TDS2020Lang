#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef struct dato dato;

typedef struct dato_tree dato_tree;

typedef struct tree tree;

typedef enum type_var_fun {INT, BOOL, VOID} type_var;

typedef enum flag_nodo {VAR, FUN, MAIN} flag_nodo;

typedef enum type_list {SYMBOL, PARAM, THREE_ADDRESS_CODE} type_list;

typedef enum flag_tree {VARIABLE, CONS, OP} flag_tree;

typedef enum op_twc {ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ} op_twc;    


//ESTRUCTURA LISTA
typedef struct nodo {
	void* info;
	struct nodo* sig;

}nodoL;

typedef struct list {
	type_list type;
	nodoL* list;
	int size;
}list;

typedef struct dato_tree {	
	enum type_var_fun type;
	char* op;
	int value;
	dato* data;
	enum flag_tree flag;
	char* temp_name;
}dato_tree;

typedef struct three_address_code {
	enum op_twc opcode;
	dato_tree* dest;
	dato_tree* op1;
	dato_tree* op2;
}three_address_code;


//ESTRUCTURA ARBOL
typedef struct tree {
	struct tree* hi;
	struct tree* hh;
	struct tree* hd;
	dato_tree* dato; // Si es un literal se usa value y sino el puntero info.
}tree;

//ESTRUCTURA VARIABLE O FUNCION
typedef struct dato {	
	enum type_var_fun type;
	char* name;
	int value;
	enum flag_nodo flag;
	list* params;
	tree* tree;
}dato;

typedef struct literal {	
	enum type_var_fun type;
	int value;
}literal;

//ESTRUCTURA NODO
typedef struct info_type {
	enum type_var_fun type;
	char* name;
}info_type;

// A structure to represent a node stack 
typedef struct stack_node {
	int level; 
	list* list;
	struct stack_node* sig;
}stack_node;




#endif
