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

void* seek(list* head, char* var);

/*
*Imprime toda la lista
*/

void show(list* head);

void show_tac(list* head);

void empty_list(list** head);

void* get(list* head, int i);

int size(list* head);

int last_insert(list* l, void* p);

#endif
