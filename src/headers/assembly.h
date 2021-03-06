#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "structures.h"
#include <stdio.h>

void gen_offset_table(list* l);

int assemble(list* l, list* ts, char* file_name);

char* resolve_assembly_name(dato_tree* curr);

void write_assembly(FILE* f, list* l, list* ts, char* file_name);

#endif
