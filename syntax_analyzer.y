%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers/table.h"
#include "headers/stack.h"

nodoL* symbol_table = NULL;
stack_node* stack = NULL;
%}	

%union { int i; char *s;}

%token<s> VOID
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


%type<s> var_decl
%type<s> var_declarations
%type<s> method_decl
%type<s> method_declar
%type<s> method_declaration
%type<s> parameters
%type<s> block
%type<s> type
%type<s> statements
%type<s> statement
%type<s> expr
%type<s> literal

%left EQ_OP
%left MULT_OP
%left PLUS_OP
%left MINUS_OP
%left AND_OP
%left ASIG_OP
%left NOT_OP
%%

program: program1{push( stack, symbol_table);};
program1:
	var_declarations {}
	|var_declarations';' method_decl {}
	| method_decl {}
	;

var_declarations:
	var_decl {}
	|var_declarations ';' var_decl {}
	;

var_decl:
	type ID {
		if(insertar(&symbol_table,$2) == 0) {
			notifyError("Duplicate variable", $2);
		}}
	;

method_decl:
	method_declar {}
	|method_decl method_declar {}
	;

method_declar:
	method_declaration block {printf("Declaration\n");}
	|EXTERN method_declaration ';' {}
	;

method_declaration:
	type ID '(' parameters ')' {}
	|VOID ID '(' parameters ')' {}
	;

parameters:
	var_decl {}
	|parameters ',' var_decl {}
	|{}
	;


block_content:
	var_declarations ';' statements {printf("Definition\n");}
	| statements {printf("Definition\n");}
	| var_declarations ';' {printf("Definition\n");}
	| {}
	;

type:
	TYPE_INTEGER {}
	|TYPE_BOOL {}
	;

statements:
	statement {printf("Statement\n");}
	|statements statement {printf("Statements\n");}
	;


statement:
	ID ASIG_OP expr ';' {printf("asig\n");}
	|RETURN expr ';' {}
	| ';' {}
	|block {printf("Declaration\n");}
	;

expr:
	ID {}
	|literal {}
	| expr PLUS_OP expr {}
	| expr MINUS_OP expr {}
	| expr EQ_OP expr {}
	| expr AND_OP expr {}
	| expr MULT_OP expr {}
	|'(' expr ')' {}
	|NOT_OP expr {}
	;


literal:
	INTEGER_LITERAL {}
	|BOOL_LITERAL {}
	;

block:
	open_brace block_content close_brace {}
	;


open_brace:
	'{' {nodoL* symbol_table = malloc(sizeof(nodoL));
		push( stack, symbol_table);}
	;

close_brace: 
	'}' {pop(stack);}
	;




