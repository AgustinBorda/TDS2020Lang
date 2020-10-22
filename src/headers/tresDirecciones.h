#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H
#include "structures.h"
#include <stdio.h>

/*
*Crea el archivo destino y escribe el codigo tres direcciones
*/

int threeCode(node* head, nodoL* sym_table);

/*
*Escribe el valor constante de root en resLoc y lo escribe en f
*/

void writeConst(node* root, char* resLoc, FILE* f);

/*
*Escribe el valor de la variable de root en resLoc
*y lo escribe en f
*/

void writeId(node* root, char* resLoc, FILE* f, nodoL* sym_table);

/*
*Realiza la operacion de root guarda el resultado en resLoc
*y lo escribe en f
*/

void writeOp(node* root, char* resLoc, FILE* f, nodoL* sym_table);

/*
*Decide el tipo de contenido de root y llama al metodo correspondiente
*/

void write(node* root, char* resLoc, FILE* f, nodoL* sym_table);

#endif
