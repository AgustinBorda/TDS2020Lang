#include <stdio.h>
#include <stdlib.h>
//#include "../headers/assembly.h"
#include "../headers/table.h"

int assemble(list* l) {
	FILE* f;
	f = fopen("assembly.txt", "w+");
	fclose(f);
	write(f, l);
	return 0;
}
//{ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ}
void write(FILE* f, list* l) {  
f =  fopen("assembly.txt", "a");      
	for(int i=0 ; i < size(l); i++) {
		three_address_code* curr = get(l,i);
		switch(curr->opcode) {
			case 0 :
			         fprintf(f, "MOV %s, EAX\n", curr->dest);
				 break;
			case 1 : fprintf(f, "MOV EAX, 0\n");
			  		 fprintf(f, "ADD EAX, %s\n", curr->op1);
			   		 fprintf(f, "ADD EAX, %s\n", curr->op2);
			         fprintf(f, "MOV %s, EAX\n", curr->dest);
				 break;
			case 2 : fprintf(f, "MOV EAX, 0\n");
			  		 fprintf(f, "ADD EAX, %s\n", curr->op1);
			   		 fprintf(f, "SUB EAX, %s\n", curr->op1);
			   		 fprintf(f, "MOV %s, EAX\n", curr->dest);
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


