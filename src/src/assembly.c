#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/assembly.h"
#include "../headers/table.h"

void gen_offset_table(list* l) {
	int init = 0;
	int i = 0;
	while( i < size(l)) {
		three_address_code* curr = get(l,i);
		if(curr -> opcode == 8) {
			init = 0;
		}
		//TODO: dato para val. constantes
		if(curr->dest != NULL &&
			       	(curr -> dest -> flag != VARIABLE || 
				 curr -> dest -> data -> flag != GLOBAL_VAR)) {
			if(curr -> dest -> data != NULL &&
				       	curr -> dest -> data -> offset != 0) {
				curr->dest->offset = curr ->dest->data->offset;
			}
			else {	
				init = init -8;
				curr->dest->offset = init;
				if(curr -> dest -> data != NULL) {
					curr -> dest -> data -> offset = init;
				}
				//TODO: Encontrar una forma mejor de hacer esto,
				//por el amor de Dios.
			}	
		}
		i++;
	}
}

int assemble(list* l, list* ts) {
	gen_offset_table(l);
	FILE* f;
	f = fopen("assembly.txt", "w+");
	fclose(f);
	write_assembly(f, l, ts);
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
		case 0:
		       	if(curr -> data -> flag == GLOBAL_VAR) {
				res = malloc(strlen(curr->data->name)+6);
				sprintf(res,"%s(%%rip)", curr->data->name);
				return res;
			}
			else {
		       		res = malloc(int_length(curr->offset)+6);
				sprintf(res,"%d(%%rbp)",curr-> offset);
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
			sprintf(res,"%d(%%rbp)",curr-> offset);    	
			return res;
	}
	return NULL;
}	


//{ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ}
void write_assembly(FILE* f, list* l, list* ts) {  
	f =  fopen("assembly.txt", "a"); 
	fprintf(f, ".file \"assembly.c\" ");
	fprintf(f, ".text");
	for (int i = 0; i < size(ts); ++i) {
		dato* curr = get(stack->list,i);
		switch(curr->flag){
			case 1: fprintf(f, ".global %s\n",curr->name);
					fprintf(f, ".type %s, @function",curr->name);
				  break;
			case 2: fprintf(f, ".global main\n");
					fprintf(f, ".type main, @function");
				  break;
			case 3: fprintf(f, ".comm %s,8,8\n",curr->name);
				  break;	  	   	  
		}
	}
	
	for(int i=0 ; i < size(l); i++) {
		three_address_code* curr = get(l,i);
		char* op1 = NULL;
		char* op2 = NULL;
		char* dest_offset = NULL;
		if (curr->op1 != NULL) {
			op1 =resolve_assembly_name(curr->op1);
		}
		if (curr->op2 != NULL) {
			op2 =resolve_assembly_name(curr->op2);
		}
		if(curr -> dest != NULL) {
			dest_offset =resolve_assembly_name(curr->dest);
		}
		switch(curr->opcode) {
			case 0 : 
				 fprintf(f, "	movq %s, %%rax\n", op1);
				 fprintf(f, "	movq %%rax, %s\n", dest_offset);
				 break;
			case 1 : 
				 fprintf(f, "	movq %s, %%rax\n", op1);
				 fprintf(f, "	addq %s, %%rax\n", op2);
				 fprintf(f, "	movq %%rax, %s\n", dest_offset);
				 break;
			case 2 : 
				fprintf(f, "	movq %s, %%rax\n", op1);
                fprintf(f, "	subq %s, %%rax\n", op2);
                fprintf(f, "	movq %%rax, %s\n", dest_offset);
				 break;
			case 3 : 
				fprintf(f, "	movq %s, %%rax\n", op1);
                fprintf(f, "	mulq %s, %%rax\n", op2);
                fprintf(f, "	movq %%rax, %s\n", dest_offset);
			   	 break;
			case 4 : 
				fprintf(f, "	movq %s, %%rax\n", op1);
                fprintf(f, "	andq %s, %%rax\n", op2);
                fprintf(f, "	movq %%rax, %s\n", dest_offset);
			   	 break;
			case 5 : 
				 fprintf(f, "	movq %s, %%rax\n", op1);
				 fprintf(f, "	negq %%rax\n");
                 fprintf(f, "	movq %%rax, %s\n", dest_offset);
			   	 break;	    	 	  	 	 
			case 6 : 
				 fprintf(f, "	movq %s, %%rax\n",op1);
			   	 fprintf(f, "	leave\n");
			   	 fprintf(f, "	ret\n");

			   	 break;	    	 	  	 	 
			case 7 : 
				 fprintf(f, "%s:\n", curr -> op1 -> data -> name);
				 fprintf(f, "	pushq %%rbp\n");
				 fprintf(f, "	movq %%rsp, %%rbp\n");
			   	 break;
			case 8 : fprintf(f, ".size	%s, .-%s\n",  curr -> op1 -> data -> name, curr -> op1 -> data -> name);	
			   	 break;
			case 9 : 
				 fprintf(f, "	movq %s, %%rax\n", op1);
			   	 fprintf(f, "	cmpq %s, %%rax\n", op2);
			   	 fprintf(f, "	sete %rax");
			   	 fprintf(f, "	movq %%rax, %s\n", dest_offset);
			   	 break;
			default : exit(1);
			  break;   	   	    	 
		}
	}
	fclose(f);        
}


