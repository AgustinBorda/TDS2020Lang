#ifndef _TABLE_H
#define _TABLE_H


#include "structures.h"


/*
* Crea una nueva lista
*/
void create_list(nodoL** p);

/*
*Inserta el nodo a la lista
*/

int insert(nodoL* head, dato d);

/*
*Busca el nodo en la lista
*/

int exist(nodoL* head, char* var);

/*
*Devuelve el valor de un identificador si existe
*en la tabla
*/

//int buscar_valor(nodoL* head, char* var);

/*
*Imprime toda la lista
*/

void show(nodoL* head);

/*
*Borra el nodo de un identificador si existe
*en la tabla
*/

int delete_node(nodoL* head, char* var);

#endif
