%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/table.h"
#include "headers/stack.h"
#include "headers/structures.h"
#include "headers/tree.h"
#include "headers/semantic_analyzer.h"

stack_node* stack;
list* l;
int has_main = 0;
void initialize() {
	createStack(&stack);	
	create_list(&l, PARAM);
}

%}	

%union { int i; char *s; struct node *n;struct tree* t;struct dato* d;struct literal* l;};

%token<s> TOKEN_VOID
%token<s> ID
%token<s> EXTERN
%token<s> RETURN
%token<s> TYPE_INTEGER
%token<s> TYPE_BOOL
%token<i> BOOL_LITERAL
%token<i> INTEGER_LITERAL
%token<s> PLUS_OP
%token<s> MINUS_OP
%token<s> EQ_OP
%token<s> AND_OP
%token<s> ASIG_OP
%token<s> NOT_OP
%token<s> MULT_OP


%type<t> var_decl
%type<t> var_declarations
%type<t> method_decl
%type<t> method_declar
%type<d> method_declaration
%type<s> parameters
%type<t> block
%type<t> block_content
%type<i> type
%type<t> statements
%type<t> statement
%type<t> expr
%type<l> literal

%left EQ_OP
%left MULT_OP
%left PLUS_OP
%left MINUS_OP
%left AND_OP
%left ASIG_OP
%left NOT_OP
%%

programInit:
	{initialize();} program {
		for(int i=0 ; i < size(stack->list); i++) {
			dato* curr = get(stack->list,i);
			if(curr -> flag == FUN || curr -> flag == MAIN) {
				if(curr -> flag == MAIN) {
					has_main = 1;
				}
				semantic_analyzer(curr);
			}
		}
		if(!has_main) {
			/*Error de main*/
		}
	}
	;

program:
	var_declarations {}
	|var_declarations method_decl {}
	| method_decl {}
	;

var_declarations:
	var_decl {}
	|var_declarations var_decl {}
	;

var_decl:
	type ID ';' {
		dato* d = malloc(sizeof(dato));
		if($1 == 0) {
			d-> type = INT;
		} 
		else {
			d-> type = BOOL;
		}
		d-> name = $2;
		d-> flag = VAR;
		int a = insert(stack->list, d);
	}
	;

method_decl:
	method_declar {}
	|method_decl method_declar {}
	;

method_declar:
	method_declaration block {
		$1-> tree = $2;
		int a = insert(stack->list, $1);
	}
	|EXTERN method_declaration ';' {	
		int a = insert(stack->list, $2);
	}
	;

method_declaration:
	type ID '(' parameters ')' {
		dato* d = malloc(sizeof(dato));
		if($1 == 0) {
			d-> type = INT;
		} 
		else {
			d-> type = BOOL;
		}
		d-> name = $2;
		d-> flag = FUN;
		d-> params = l;
		$$ = d;
	}
	|TOKEN_VOID ID '(' parameters ')' {
		dato* d = malloc(sizeof(dato));
		d-> type = VOID;
		if(strcmp($2,"main") == 0) {
			d-> flag = MAIN;
		} 
		else {
			d-> type = FUN;
		}
		d-> name = $2;
		d-> params = l;
		$$ = d;
	}
	;

parameters:
	var_decl_params {}
	|parameters ',' var_decl_params {}
	|{}
	;

var_decl_params:
	type ID {
		info_type* inf = malloc(sizeof(info_type));
		if($1 == 0) {
			inf-> type = INT;
		} 
		else {
			inf-> type = BOOL;
		}
		inf->name = $2;
		insert(l, inf);
	}
	;

block_content:
	var_declarations statements {$$ = $2;}
	| statements {$$ = $1;}
	| var_declarations {$$ = NULL;}
	| {$$ = NULL;}
	;

type:
	TYPE_INTEGER {$$ = 0;}
	|TYPE_BOOL {$$ = 1;}
	;

statements:
	statement {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = ";";
		$$ = load_node($1, NULL, NULL, d);
	}
	|statements statement {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = ";";
		$$ = load_node($1, NULL, $2, d);
	}
	;


statement:
	 ID ASIG_OP expr ';' {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "=";	
		dato_tree* d2 = malloc(sizeof(dato_tree));
		d2-> flag = VARIABLE;
		d2-> data = seek(stack->list, $1);
		dato* ptr = d2->data;
		d2 -> type = ptr -> type;
		tree* hi = load_node(NULL, NULL, NULL, d2);
		$$ = load_node(hi, NULL, $3, d);
	}
	|RETURN expr ';' {	
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "RETURN";
		$$ = load_node($2, NULL, NULL, d);
	}
	|RETURN ';' {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "RETURN";
		$$ = load_node(NULL, NULL, NULL, d);
	}
	| ';' {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = ";";
		$$ = load_node(NULL, NULL, NULL, d);
	}
	|block {$$ = $1;}
	;

expr:
	ID {				
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = VARIABLE;
		d-> data = seek(stack->list, $1);
		dato* ptr = d->data;
		d -> type = ptr -> type;
		$$ = load_node(NULL, NULL, NULL, d);
	}
	|literal {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = CONS;
		d-> type = $1 -> type;
		d-> value =  $1 -> value;
		free($1);
		$$ = load_node(NULL, NULL, NULL, d);
	}
	| expr PLUS_OP expr {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "+";
		$$ = load_node($1, NULL, $3, d);
	}
	| expr MINUS_OP expr {
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "-";
		$$ = load_node($1, NULL, $3, d);
	}
	| expr EQ_OP expr {//
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "==";
		$$ = load_node($1, NULL, $3, d);
	}
	| expr AND_OP expr {//
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "&&";
		$$ = load_node($1, NULL, $3, d);
	}
	| expr MULT_OP expr  {	
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "*";
		$$ = load_node($1, NULL, $3, d);
	}
	|'(' expr ')' {$$ = $2;}
	|NOT_OP expr {//
		dato_tree* d = malloc(sizeof(dato_tree));
		d-> flag = OP;
		d-> op = "!";
		$$ = load_node($2, NULL, NULL, d);
	}
	;


literal:
       INTEGER_LITERAL { 
		literal* l = malloc(sizeof(literal));
		l -> type = 0;
		l -> value = $1;
		$$ = l;
	}
	|BOOL_LITERAL {
		literal* l= malloc(sizeof(literal));
		l -> type = 1;
		l -> value = $1;
		$$ = l;
	}
	;

block:
	open_brace block_content close_brace {$$ = $2;}
	;


open_brace:
	'{' {
		push(&stack);
		for(int i=0 ; i < size(l); i++) {
			dato* inf = malloc(sizeof(dato));
			info_type* current = get(l,i);
                	inf->type = current->type;
                	inf->name = current->name;
			inf->flag = VAR;
                	insert(stack->list,inf);
		}
		create_list(&l, PARAM);
	}
	;

close_brace: 
	'}' {pop(&stack);}
	;




