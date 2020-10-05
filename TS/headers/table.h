#ifndef _TABLE_H
#define _TABLE_H


#include "structures.h"

/*
*Inserta el nodo a la lista
*/

int insertar(nodoL** head, dato d);

/*
*Busca el nodo en la lista
*/

int existe(nodoL* head, char* var);

/*
*Devuelve el valor de un identificador si existe
*en la tabla
*/

int buscar_valor(nodoL* head, char* var);

/*
*Imprime toda la lista
*/

int mostrar(nodoL* head);

/*
*Borra el nodo de un identificador si existe
*en la tabla
*/

void borrar(nodoL** head, char* var);

#endif
