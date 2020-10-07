#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef enum type_var_fun {INT, BOOL, VOID} type_var;

typedef enum flag_nodo {VAR, FUN, MAIN} flag_nodo;

//ESTRUCTURA VARIABLE O FUNCION
typedef struct dato {	
	enum type_var_fun type;
	char* name;
	int value;
	enum flag_nodo flag;
	//TODO: Lista de tipos para funciones
}dato;

//ESTRUCTURA LISTA
typedef struct nodo {
	dato* info;
	struct nodo* sig;

}nodoL;

//ESTRUCTURA NODO
typedef struct nodo_type {
	enum type_var_fun type;
	struct nodo *sig;
}nodoType;

// A structure to represent a node stack 
typedef struct stack_node {
	int level; 
	nodoL* list;
	struct stack_node* sig;
}stack_node;


//ESTRUCTURA ARBOL
typedef struct node {
	struct node* hi;
	struct node* hd;
	struct node* hh;
	nodoL* info;
	int value; // Si es un literal se usa value y sino el puntero info.
}node;



#endif
