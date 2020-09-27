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
%token<s> ARITH_OP
%token<s> COND_OP
%token<s> REL_OP


%type var_decl
%type var_declarations
%type method_decl
%type method_declar
%type method_declaration
%type parameters
%type block
%type type
%type statements
%type statement
%type expr
%type bin_op
%type literal


%%

program : var_declarations method_decl

var_declarations : var_decl                       {}
		  |var_decl var_declarations                  {}
      |{}

var_decl : type ID ';'                            {printf("%s\n", "variable declarada");}
       

method_decl : method_declar                       {}
	     |method_declar method_decl                 {}
       |{}

method_declar : method_declaration block          {}
	       |EXTERN method_declaration ';'           {}

method_declaration : type ID '(' parameters ')'   {}
	            |VOID ID '(' parameters ')'         {}

parameters : type ID ',' parameters               {}
	    |{}

block : '{' var_declarations statements '}'       {}

type : TYPE_INTEGER                               {}
      |TYPE_BOOL                                  {}

statements : statement                            {}
	    |statement statements                       {}
      |{}

statement : ID '=' expr ';'                       {}
           |RETURN expr ';'                       {}
           |';'                                   {}
           |block                                 {}

expr : ID                                         {}
      |literal                                    {}
      |expr bin_op expr                           {}
      |'!' expr                                   {}
      |'(' expr ')'                               {}

bin_op : ARITH_OP                                 {} 
        |REL_OP                                   {}
        |COND_OP                                  {}

literal : INTEGER_LITERAL                         {}
	 |BOOL_LITERAL                                  {}
