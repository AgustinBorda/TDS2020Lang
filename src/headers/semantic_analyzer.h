#ifndef _SEMANTIC_ANALYZER_H_
#define _SEMANTIC_ANALYZER_H_
#include "structures.h"
void semantic_analyzer(dato* t);
void type_error(char* msg);
enum type_var_fun analyze_types(tree* t);
void analyze(tree* t);
void semantic_analyzer(dato* t);
#endif

