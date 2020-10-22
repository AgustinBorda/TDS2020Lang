#include <stdio.h>
#include <stdlib.h>
#include "../headers/tresDirecciones.h"
#include "../headers/table.h"
#include "../headers/tempGen.h"
/*void create_file() {
	FILE* f;
	f = fopen("threeCode.txt", "w+");
	fclose(f);
}*/

int threeCode(dato* t, list* l) {
	tree* tr = t -> tree;
	write(tr, l);
	return 0;
}


struct address writeConst(node* root) {
		address* ad = malloc(sizeof(address));
		ad -> data = root->dato;
		return ad;
}

struct address writeId(tree* root) {
	if(exist(l, root->dato->name)) {
		address* ad = malloc(sizeof(address));
		ad -> name =  root->dato->name;
		ad -> data = root->dato;
		return ad;
	}
	return NULL;// hacer mensaje de error
}

void writeOp(node* root, list* l) {
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

void write(tree* root,list* l) {
        switch(root->dato->flag) {
		case 0 : return writeId(root,l);
			 break;
		case 1 : return writeConst(root,l);
			 break;
		case 2 : return writeOp(root,l);
			 break;
		default : exit(1);
			  break;
	}
}

