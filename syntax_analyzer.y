%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

%left NOT_OP
%left EQ_OP
%left PLUS_OP
%left MINUS_OP
%left AND_OP
%left ASIG_OP
%%

program:
	var_declarations {}
	|var_declarations';' method_decl {}
	| method_decl {}
	;

var_declarations:
	var_decl {}
	|var_declarations ';' var_decl {}
	;

var_decl:
	type ID {}
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
	type ID '(' parameters ')' {}
	|VOID ID '(' parameters ')' {}
	;

parameters:
	var_decl {}
	|parameters ',' var_decl {}
	|{}
	;


block:
	'{' var_declarations ';' statements '}' {}
	|'{' statements '}' {}
	| '{''}' {}
	;

type:
	TYPE_INTEGER {}
	|TYPE_BOOL {}
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
	ID {}
	|literal {}
	| expr PLUS_OP expr {}
	| expr MINUS_OP expr {}
	| expr EQ_OP expr {}
	| expr AND_OP expr {}
	|'(' expr ')' {}
	|NOT_OP expr {}
	;


literal:
	INTEGER_LITERAL {}
	|BOOL_LITERAL {}
	;



