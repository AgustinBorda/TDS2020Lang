#include <stdio.h>
#include <stdlib.h>
//#include "../headers/assembly.h"
#include "../headers/table.h"

int init = 0;
void gen_offset_table(list* l) {
	int i = 0;
	while( i < size(l) && get(l,i)->opcode != 8) {
		three_address_code* curr = get(l,i);
		if(curr->dest != NULL) {
			if (curr->op1->flag == 0){
				init = init-8;
				curr -> op1 -> offset = init;
			}
			if (curr->op2->flag == 0){
				init = init-8;
				curr -> op2 -> offset = init;
			}	
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
//{ASSIGN, ADD, SUB, MULT, AND, NOT, RET, INIT_FUN, END_FUN, EQ}
void write(FILE* f, list* l) {  
f =  fopen("assembly.txt", "a");      
	for(int i=0 ; i < size(l); i++) {
		three_address_code* curr = get(l,i);
		switch(curr->opcode) {
			case 0 :switch(curr -> op2 -> flag){
					 case 0 :  fprintf(f, "movl $%d, %d(%rbp)\n", curr->op2->data->value , curr->op1->offset);
					 		   fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op1->offset);  
						  break;
					 case 1 : fprintf(f, "movl $%d, %d(%rbp)\n", curr->op2->value , curr->op1->offset);
					 		  fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op1->offset);  
				 		  break;
				 	 default : exit(1);
						  break;	  
				 break;
			case 1 : switch(curr -> op1 -> flag){
					 case 0 : switch(curr -> op2 -> flag){
							  	case 0 : fprintf(f, "movl $%d(%rbp), (%%edx)\n", curr->op1->offset);
									   fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op2->offset);
									   fprintf(f, "addl (%%edx), (%%eax)\n");
									   break;
								  case 1 : fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op1->offset);
									   fprintf(f, "addl $%d, (%%eax)\n",curr->op2->value);
									   break;
								  default : exit(1);
							 	 	    break;
							  }
						  break;
					case 1 :  switch(curr -> op2 -> flag){
                                 	case 0 : fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op2->offset);
                                             fprintf(f, "addl $%d, (%%eax)\n",curr->op1->value);
                                         break;
                                    case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->value);
                                             fprintf(f, "addl $%d, (%%eax)\n", curr->op2->value);
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
							      case 0 : fprintf(f, "movl $%d(%rbp), (%%edx)\n", curr->op1->offset);
									     fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op2->offset);
									     fprintf(f, "subl (%%edx), (%%eax)\n");
									   break;
								  case 1 : fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op1->offset);
									  	   fprintf(f, "subl $%d, (%%eax)\n",curr->op2->value);
									   break;
								  default : exit(1);
							 	 	    break;
							  }
						  break;
					case 1 :  switch(curr -> op2 -> flag){
                                 	case 0 : fprintf(f, "movl $%d(%rbp), (%%eax)\n", curr->op2->offset);
                                             fprintf(f, "subl $%d, (%%eax)\n",curr->op1->value);
                                         break;
                                    case 1 : fprintf(f, "movl $%d, (%%eax)\n", curr->op1->value);
                                             fprintf(f, "subl $%d, (%%eax)\n", curr->op2->value);
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


