#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "../headers/assembly.h"
#include "../headers/table.h"

void gen_offset_table(list* l) {
	int init = 0;
	int i = 0;
	while( i < size(l) && get(l,i)->opcode != 8) {
		three_address_code* curr = get(l,i);
		if(curr->dest != NULL) {
			init = init -8;
			curr->dest->offset = init;	
		}
	}
}

int assemble(list* l) {
	gen_offset_table(l);
	FILE* f;
	f = fopen("assembly.txt", "w+");
	fclose(f);
	write(f, l);
	return 0;
}
//TODO: Move this to a "utils" file.
int int_length(int n) {
	if(n == 0) {
		return 1;
	}
	return floor(log10(abs(n))) + 1;
}
//
char* resolve_assembly_name(dato_tree* curr) {
	char* res;
	switch (curr -> flag) {
		case 0: if(curr -> data -> flag == GLOBAL_VAR) {
				res = malloc(strlen(curr->data->name)+6);
				sprintf(res,"%s(%rip)", curr->data->name);
				return res;
			}
			else {
		       		res = malloc(int_length(curr->offset)+6);
				sprintf(res,"%d(%rbp)",curr-> offset);
				return res;
			}
			break;
		case 1: 
			res = malloc(int_length(curr->value)+1);
			sprintf(res,"$%d",curr->value);
			return res;
			break;
		default:
			res = malloc(int_length(curr->offset)+6);
			sprintf(res,"%d(%rbp)",curr-> offset);    	
			return res;
	}
	return NULL;
}	


//{ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ}
void write(FILE* f, list* l) {  
f =  fopen("assembly.txt", "a");      
	for(int i=0 ; i < size(l); i++) {
		three_address_code* curr = get(l,i);
		if (curr->op1 != NULL)
			char* op1 =resolve_assembly_name(curr->op1);
		if (curr->op2 != NULL)
			char* op2 =resolve_assembly_name(curr->op2);
		char* dest_offset =resolve_assembly_name(curr->dest);
		switch(curr->opcode) {
			case 0 : fprintf(f, "movl $%s, %%eax\n", op1);
				 fprintf(f, "movl %%eax, %s\n", dest_offset);
				 break;
			case 1 : fprintf(f, "movl $%s, %%eax\n", op1);
				 fprintf(f, "addl $%s, %%eax\n", op2);
				 fprintf(f, "movl %%eax, %s\n", dest_offset);
				 break;
			case 2 : fprintf(f, "movl $%s, %%eax\n", op1);
                                 fprintf(f, "subl $%s, %%eax\n", op2);
                                 fprintf(f, "movl %%eax, %s\n", dest_offset);
				 break;
			case 3 : fprintf(f, "movl $%s, %%eax\n", op1);
                                 fprintf(f, "mull $%s, %%eax\n", op2);
                                 fprintf(f, "movl %%eax, %s\n", dest_offset);
			   	 break;
			case 4 : fprintf(f, "movl $%s, %%eax\n", op1);
                                 fprintf(f, "andl $%s, %%eax\n", op2);
                                 fprintf(f, "movl %%eax, %s\n", dest_offset);
			   	 break;
			case 5 : fprintf(f, "movl $%s, %%eax\n", op1);
				 fprintf(f, "negl %%eax\n");
                                 fprintf(f, "movl %%eax, %s\n", dest_offset);
			   	 break;	    	 	  	 	 
			case 6 : 
			   	 fprintf(f, "ret\n");	 
			   	 break;	    	 	  	 	 
			case 7 : fprintf(f, "endbr64\n");
				 fprintf(f, "pushq %rbp\n");
				 fprintf(f, "movq %rsp, %rbp\n");
			   	 break;
			case 8 : fprintf(f, "popq %rbp\n");
			   	 break;
			case 9 : fprintf(f, "movl $%s, %%eax\n", op1);
			   	 fprintf(f, "cmpl %s, %%eax\n", op2);
			   	 fprintf(f, "movl %%eax, %s\n", dest_offset);
			   	 break;
			default : exit(1);
			  break;   	   	    	 
		}
	}
	fclose(f);        
}


