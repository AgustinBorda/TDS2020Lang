#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/assembly.h"
#include "../headers/table.h"

//TODO: Move this to a "utils" file.
int int_length(int n) {
	if(n == 0) {
		return 1;
	}
	return floor(log10(abs(n))) + 1;
}
int next_16_multiple(int n) {
	if(n%16 != 0) {
		return n +(16-n%16);
	}
	return n;
}
//
void gen_offset_table(list* l) {
	int init = 0;
	int i = 0;
	int* fun_max_offset = NULL;
	while( i < size(l)) {
		three_address_code* curr = get(l,i);
		if(curr -> opcode == 7) {
			init = 0;
			fun_max_offset = &(curr -> op1 -> data -> offset); 
		}
		if(curr -> opcode == 8) {
			*fun_max_offset = next_16_multiple(*fun_max_offset);
		}
		//TODO: dato para val. constantes
		if(curr->dest != NULL &&
				(curr -> dest -> flag != VARIABLE || 
				 curr -> dest -> data -> flag != GLOBAL_VAR) &&
				curr -> opcode != RET) {
			if(curr -> dest -> data != NULL &&
					curr -> dest -> data -> offset != 0) {
				curr->dest->offset = curr ->dest->data->offset;
			}
			else {	
				init = init -8;
				curr->dest->offset = init;
				*fun_max_offset = *fun_max_offset + 8;
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

int assemble(list* l, list* t, char* file_name) {
	gen_offset_table(l);
	printf("offsets bien\n");
	FILE* f;
	char* ext_file_name = malloc((strlen(file_name)+2)*sizeof(char));
	sprintf(ext_file_name, "%s.s",file_name);
	f = fopen(ext_file_name, "w+");
	fclose(f);
	write_assembly(f, l, t, ext_file_name);
	return 0;
}
char* resolve_assembly_name(dato_tree* curr) {
	char* res;
	switch (curr -> flag) {
		case 0:
			if(curr -> data -> flag == GLOBAL_VAR) {
				res = malloc((strlen(curr->data->name)+6)*sizeof(char));
				sprintf(res,"%s(%%rip)", curr->data->name);
				return res;
			}
			else {
				res = malloc((int_length(curr->offset)+6)*sizeof(char));
sprintf(res,"%d(%%rbp)",curr -> data -> offset);
				return res;
			}
			break;
		case 1: 
			res = malloc((int_length(curr->value)+1)*sizeof(char));
			sprintf(res,"$%d",curr->value);
			return res;
			break;
		case 4 : return curr -> temp_name;
			 break;
		default:
			res = malloc((int_length(curr->offset)+6)*sizeof(char));
			sprintf(res,"%d(%%rbp)",curr-> offset);    	
			return res;
	}
	return NULL;
}	


//{ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ}
void write_assembly(FILE* f, list* l, list* ts, char* file_name) {  
	f =  fopen(file_name, "a"); 
	fprintf(f, ".file \"%s.ctds\"\n",strtok(file_name, "."));
	fprintf(f, ".text\n");
	//	fprintf(f, ".globl %s", );


	/*.file	"ejem.c"
	  .text
	  .globl	main
	  .type	main, @function
	  */    
	for (int i = 0; i < size(ts); ++i) {
		dato* curr = get(ts,i);
		if(curr -> flag == 3) {
			fprintf(f, ".comm %s,8,8\n",curr->name);
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
				fprintf(f, "	imulq %s, %%rax\n", op2);
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
				fprintf(f, "	and $0x1, %%rax\n");
				fprintf(f, "	movq %%rax, %s\n", dest_offset);
				break;	    	 	  	 	 
			case 6 :
			       	if (op1 != NULL) {	
					fprintf(f, "	movq %s, %%rax\n", op1);
				}
				fprintf(f, "	leave\n");
				fprintf(f, "	ret\n");
				break;	    	 	  	 	 
			case 7 : 
				fprintf(f, ".globl %s\n", curr -> op1 -> data -> name);	
				fprintf(f, ".type %s, @function\n", curr -> op1 -> data -> name);
				fprintf(f, "%s:\n", curr -> op1 -> data -> name);
				fprintf(f, "	pushq %%rbp\n");
				fprintf(f, "	movq %%rsp, %%rbp\n");
				if (curr -> op1 -> data -> offset > 0) {
					fprintf(f, "	subq $%d, %%rsp\n", curr -> op1 -> data -> offset);
				}
				break;
			case 8 : fprintf(f, ".size %s, .-%s\n",  curr -> op1 -> data -> name, curr -> op1 -> data -> name);
				 break;
			case 9 : 
				 fprintf(f, "	movq %s, %%rax\n", op1);
				 fprintf(f, "	cmpq %s, %%rax\n", op2);
				 fprintf(f, "	sete %%al\n");
				 fprintf(f, "	movzbq %%al, %%eax\n");
				 fprintf(f, "	movq %%rax, %s\n", dest_offset);
				 break;
			case 10 : //MINOR
				 fprintf(f, "	movq %s, %%rax\n", op1);
				 fprintf(f, "	cmpq %s, %%rax\n", op2);
				 fprintf(f, "	setl %%al\n");
				 fprintf(f, "	movzbq %%al, %%rax\n");
				 fprintf(f, "	movq %%rax, %s\n", dest_offset);
				break;
			case 11 : //JUMP
				fprintf(f, "	jmp .%s\n", op1);
				break;
			case 12 : //LABEL
				fprintf(f, ".%s:\n", op1);
				break;
			case 13 : //IF_FALSE
				printf("tuqui\n");
				fprintf(f, "	movq %s, %%rax\n", op1);
				fprintf(f, "	cmpq $0, %%rax\n");
				fprintf(f, "	jz .%s\n", op2);
				break;
			case 14 : //IF_TRUE	
				fprintf(f, "	movq %s, %%rax\n", op1);
				fprintf(f, "	cmpq $1, %%rax\n");
				fprintf(f, "	jz .%s\n", op2);
				break;
			default : exit(1);
				  break;   	   	    	 
		}
	}
	fclose(f);        
}


