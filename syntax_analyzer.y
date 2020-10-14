%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/table.h"
#include "headers/stack.h"
//#include "headers/tree.h"

stack_node* stack;
list* l;
void initialize() {
	createStack(&stack);	
}
void init_list() {
	create_list(&l, PARAM);
}


%}	

%union { int i; char *s; struct node *n;struct dato* d};

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


%type<n> var_decl
%type<n> var_declarations
%type<n> method_decl
%type<n> method_declar
%type<n> method_declaration
%type<s> parameters
%type<n> block
%type<i> type
%type<n> statements
%type<n> statement
%type<n> expr
%type<n> literal

%left EQ_OP
%left MULT_OP
%left PLUS_OP
%left MINUS_OP
%left AND_OP
%left ASIG_OP
%left NOT_OP
%%

programInit:
	   {initialize();} {init_list();} program {}
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
		if(a==1) {
			show(stack->list);
		}
		 else {
			printf("Error,no se cargo");
		}
	}
	;

method_decl:
	  method_declar {}
	|method_decl method_declar {}
	;

method_declar:
	     method_declaration block {}
	|EXTERN method_declaration ';' {}
	;

method_declaration:
		  type ID '(' parameters ')' {
		  		dato* d = malloc(sizeof(dato));
				printf("%d\n",$1);
				if($1 == 0) {
					d-> type = INT;
					printf("%d\n",d->type);
				} 
				else {
					d-> type = BOOL;
					printf("%d\n",d->type);
				}
				d-> name = $2;
				d-> flag = FUN;
				d-> params = l;
				init_list();
				
				int a = insert(stack->list, d);
				if(a==1) {
					show(stack->list);
					show(d->params);
				}
		 		else {
					printf("Error,no se cargo");
				}
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
									init_list();
								    int a = insert(stack->list, d);
									if(a==1) {
										show(stack->list);
									}
		 							else {
										printf("Error,no se cargo");
									}
									}
	;

parameters:
	var_decl_params {}
	|parameters ',' var_decl_params {}
	|{}
	;

var_decl_params:
	type ID  {	info_type* inf = malloc(sizeof(info_type));
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
	var_declarations statements {$$ = $2}
	| statements {$$ = $1}
	| var_declarations {}
	| {}
	;

type:
	TYPE_INTEGER {$$ = 0;}
	|TYPE_BOOL {$$ = 1;}
	;

statements:
	  statement {}
	|statements statement {}
	;


statement:
	 ID ASIG_OP expr ';' {}
	|RETURN expr ';' {}
	| ';' {}
	|block {}
	;

expr:
    	ID                  {padre = $1; info = seek(symbol, $1); hi = NULL; hm = NULL; nd = NULL}
	|literal             {}
	| expr PLUS_OP expr  {}
	| expr MINUS_OP expr {}
	| expr EQ_OP expr    {}
	| expr AND_OP expr   {}
	| expr MULT_OP expr  {}
	|'(' expr ')'        {}
	|NOT_OP expr         {}
	;


literal:
       INTEGER_LITERAL {}
	|BOOL_LITERAL {}
	;

block:
     open_brace block_content close_brace { $$ = $2 }
	;


open_brace:
	  '{' {push(&stack);}
	;

close_brace: 
	   '}' {pop(&stack);}
	;




