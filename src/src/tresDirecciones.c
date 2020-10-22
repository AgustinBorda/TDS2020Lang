#include <stdio.h>
#include <stdlib.h>
#include "../headers/tresDirecciones.h"
#include "../headers/table.h"
#include "../headers/tempGen.h"
int threeCode(node* head, nodoL* sym_table) {
	FILE* f;
	f = fopen("threeCode.txt", "w+");
	fclose(f);
	write(head, "RESULT", f, sym_table);
	return 0;
}


void writeConst(node* root, char* resLoc, FILE* f) {
	f =  fopen("threeCode.txt", "a");
	fprintf(f,"MOV %s, %d\n", resLoc, root->data.value);
	fclose(f);
}

void writeId(node* root, char* resLoc, FILE* f, nodoL* sym_table) {
	if(existe(sym_table, root->data.var.name)) {
		f =  fopen("threeCode.txt", "a");
		fprintf(f,"MOV %s, %d\n", resLoc, buscar_valor(sym_table, root->data.var.name));
		fclose(f);
	}
}

void writeOp(node* root, char* resLoc, FILE* f, nodoL* sym_table) {
	char* leftVal = genTemp();
	char* rightVal = genTemp();
	if(root -> hi != NULL) {
		write(root->hi, leftVal, f, sym_table);
	}
	else {
		exit(1);
	}
	if(root -> hd != NULL) {
		write(root->hd, rightVal, f, sym_table);
	}
	else {
		exit(1);
	}
	f =  fopen("threeCode.txt", "a");
	switch (root->data.op) {
		case '+' : fprintf(f, "MOV EAX, 0\n");
			   fprintf(f, "ADD EAX, %s\n", leftVal);
			   fprintf(f, "ADD EAX, %s\n", rightVal);
			   fprintf(f, "MOV %s, EAX\n", resLoc);
			   break;
                case '-' : fprintf(f, "MOV EAX, 0\n");
			   fprintf(f, "ADD EAX, %s\n", leftVal);
			   fprintf(f, "SUB EAX, %s\n", rightVal);
			   fprintf(f, "MOV %s, EAX\n", resLoc);
			   break;
		case '*' : fprintf(f, "MOV EAX, 0\n");
			   fprintf(f, "ADD EAX, %s\n", leftVal);
			   fprintf(f, "MUL EAX, %s\n", rightVal);
			   fprintf(f, "MOV %s, EAX\n", resLoc);
			   break;
		case '/' : fprintf(f, "MOV EAX, 0\n");
			   fprintf(f, "ADD EAX, %s\n", leftVal);
			   fprintf(f, "DIV EAX, %s\n", rightVal);
		           fprintf(f, "MOV %s, EAX\n", resLoc);
			   break;
		default : exit(1);
			  break;
		}
	fclose(f);
}

void write(node* root, char* resLoc, FILE* f, nodoL* sym_table) {
        switch(root->flag) {
		case 0 : return writeId(root, resLoc, f, sym_table);
			 break;
		case 1 : return writeConst(root, resLoc, f);
			 break;
		case 2 : return writeOp(root, resLoc, f, sym_table);
			 break;
		default : exit(1);
			  break;
	}
}
