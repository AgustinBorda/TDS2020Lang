#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef enum type_var_fun {INT, BOOL, VOID} type_var;

typedef enum flag_nodo {VAR, FUN, MAIN} flag_nodo;

typedef enum type_list {SYMBOL, PARAM, TREE} type_list;

//ESTRUCTURA LISTA
typedef struct nodo {
	void* info;
	struct nodo* sig;

}nodoL;


typedef struct list {
	type_list type;
	nodoL* list;
}list;

//ESTRUCTURA VARIABLE O FUNCION
typedef struct dato {	
	enum type_var_fun type;
	char* name;
	int value;
	enum flag_nodo flag;
	list* params;
}dato;

//ESTRUCTURA NODO
typedef struct info_type {
	enum type_var_fun type;
	char* name;
}info_type;

// A structure to represent a node stack 
typedef struct stack_node {
	int level; 
	nodoL* list;
	struct stack_node* sig;
}stack_node;


//ESTRUCTURA ARBOL
typedef struct tree {
	struct tree* hi;
	struct tree* hd;
	struct tree* hh;
	nodoL* info;
	int value; // Si es un literal se usa value y sino el puntero info.
}tree;



#endif
