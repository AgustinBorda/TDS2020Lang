#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef enum flag_nodo {VAR, FUN, MAIN} flag_nodo;

//ESTRUCTURA LISTA
typedef struct nodo {
	enum flag_nodo flag;
	dato info;
	struct nodo *sig;

}nodoL;

typedef enum type_var_fun {INT, BOOL, VOID} type_var;

//ESTRUCTURA VARIABLE O FUNCION
typedef struct dato {	
	enum type_var_fun type;
	char* name;
	int value;
	nodoL* sig;
}dato;


// A structure to represent a node stack 
typedef struct stack_node {
	int level; 
	nodoL* sig;
	struct stack_node *sig;
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
