#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef enum type_var_fun {INT, BOOL, VOID} type_var;

typedef enum flag_nodo {VAR, FUN, MAIN} flag_nodo;

typedef enum type_list {SYMBOL, PARAM, TREE} type_list;

typedef enum flag_tree {VARIABLE, CONS, OP} flag_tree;

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
	void* data; //SIEMPRE CASTEAR A dato*
	enum flag_tree flag;
}dato_tree;

//ESTRUCTURA ARBOL
typedef struct tree {
	struct tree* hi;
	struct tree* hd;
	struct tree* hh;
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
	int type;
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
