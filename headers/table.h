#ifndef _TABLE_H
#define _TABLE_H


#include "structures.h"


/*
* Crea una nueva lista
*/
void create_list(list** p, type_list type);


/*
*Inserta el nodo a la lista
*/

int insert(list* head, void* d);

/*
*Busca el nodo en la lista
*/

int exist(list* head, char* var);

/*
*Devuelve el valor de un identificador si existe
*en la tabla
*/

//int buscar_valor(nodoL* head, char* var);

/*
*Imprime toda la lista
*/

void show(list* head);

/*
*Borra el nodo de un identificador si existe
*en la tabla
*/

int delete_node(list* head, char* var);

void empty_list(list** head);

#endif
