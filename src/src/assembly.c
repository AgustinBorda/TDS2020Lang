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
		switch(curr->opcode) {
			case 0 :
				char* op1_name = resolve_assembly_name(curr -> op1);
				char* dest_name = resolve_assembly_name(curr->dest);
				fprintf(f, "movl %s, %%eax\n", op1_name);
				fprintf(f, "movl %%eax, %s\n", dest_name); //dest_name = -24(rbp) 
				 break;
			case 1 : switch(curr -> op1 -> flag){
					 case 0 : switch(curr -> op2 -> flag){
							  	  case 0 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->data->value);
									       fprintf(f, "addl $%d, (%%eax)\n", curr->op2->data->value);
									       fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
									   break;
								  case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->data->value);
									       fprintf(f, "addl $%d, (%%eax)\n",curr->op2->value);
									       fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
									   break;
								  default : exit(1);
							 	 	    break;
							  }
						  break;
					case 1 :  switch(curr -> op2 -> flag){
                                 	case 0 : fprintf(f, "movl $%d, (%%eax)\n", curr->op2->data->value);
                                             fprintf(f, "addl $%d, (%%eax)\n",curr->op1->value);
                                             fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
                                         break;
                                    case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->value);
                                             fprintf(f, "addl $%d, (%%eax)\n", curr->op2->value);
                                             fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
                                         break;
                                    default : exit(1);
                                         break;
                               }
                          break;
					default : exit(1);
                          break;
				 }
				 break;
			case 2 : switch(curr -> op1 -> flag){
					 case 0 : switch(curr -> op2 -> flag){
							  	  case 0 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->data->value);
									       fprintf(f, "subl $%d, (%%eax)\n", curr->op2->data->value);
									       fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
									   break;
								  case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->data->value);
									       fprintf(f, "subl $%d, (%%eax)\n",curr->op2->value);
									       fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
									   break;
								  default : exit(1);
							 	 	    break;
							  }
						  break;
					case 1 :  switch(curr -> op2 -> flag){
                                 	case 0 : fprintf(f, "movl $%d, (%%eax)\n", curr->op2->data->value);
                                             fprintf(f, "subl $%d, (%%eax)\n",curr->op1->value);
                                             fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
                                         break;
                                    case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->value);
                                             fprintf(f, "subl $%d, (%%eax)\n", curr->op2->value);
                                             fprintf(f, "movl (%%eax), %d(rbp)\n", curr->dest->offset);
                                         break;
                                    default : exit(1);
                                         break;
                               }
                          break;
					default : exit(1);
                          break;
				 }
				 break;
			case 3 : fprintf(f, "MOV EAX, 0\n");
			   		 fprintf(f, "ADD EAX, %s\n", curr->op1);
			   		 fprintf(f, "MUL EAX, %s\n", curr->op2);
			   		 fprintf(f, "MOV %s, EAX\n", curr->dest);
			   	 break;
			case 4 : fprintf(f, "MOV EAX, 0\n");
			   		 fprintf(f, "ADD EAX, %s\n", curr->op1);
			   		 fprintf(f, "AND EAX, %s\n", curr->op2);
			   		 fprintf(f, "MOV %s, EAX\n", curr->dest);
			   	 break;
			case 5 : 
			   		 fprintf(f, "NEG EAX, %s\n", curr->dest);
			   	 break;	    	 	  	 	 
			case 6 : 
			   		 fprintf(f, "RET EAX, %s\n", curr->dest);	 
			   	 break;	    	 	  	 	 
			case 7 : //TODO
			   	 break;
			case 8 : //TODO
			   	 break;
			case 9 : fprintf(f, "MOV EAX, 0\n");
			   		 fprintf(f, "ADD EAX, %s\n", curr->op1);
			   		 fprintf(f, "CMP EAX, %s\n", curr->op2);
			   		 fprintf(f, "MOV %s, EAX\n", curr->dest);
			   	 break;
			default : exit(1);
			  break;   	   	    	 
		}
	}
	fclose(f);        
}


