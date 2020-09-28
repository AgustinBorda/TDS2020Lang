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
%type<s> bin_op
%type<s> literal


%%

program : var_declarations method_decl

var_declarations : var_decl                       {}
		  |var_declarations var_decl                  {}
    

var_decl : type ID ';'                            {printf("%s\n", "variable declarada");}
       

method_decl : method_declar                       {}
	     |method_decl method_declar                 {}

method_declar : method_declaration block          {}
	       |EXTERN method_declaration ';'           {printf("%s\n", "metodo declarada");}

method_declaration : type ID '(' parameters ')'   {}
	            |VOID ID '(' parameters ')'         {}

parameters : parameter               {}
	    |parameter parameters    {}
            |{}

parameter : type ID                            {}

block : '{' var_declarations statements '}'       {}

type : TYPE_INTEGER                               {}
      |TYPE_BOOL                                  {}

statements : statement                            {}
	    |statements statement                       {}
     

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
