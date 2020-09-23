%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//REGISTRO TYPE (esto hiria en estructures.h)
typedef enum type {INTEGER, BOOL, VOID,UNDEFINED}type;

%}	
 
%union { int i; char *s; boolean b; enum type t} 

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
%type id

%%

program : var_declarations method_decl

var_declarations : var_decl                       {}
		  |var_decl var_declarations      {}
                  |{}

var_decl : type id ';'                            {}

method_decl : method_declar                       {}
	     |method_declar method_decl           {}
             |{}

method_declar : method_declaration block          {}
	       |extern method_declaration ';'     {}

method_declaration : type id '(' parameters ')'   {}
	            |void id '(' parameters ')'   {}

parameters : type id ',' parameters               {}
	    |{}

block : '{' var_declarations statements '}'       {}

type : integer                                    {}
      |bool                                       {}

statements : statement                            {}
	    |statement statements                 {}
            |{}

statement : id '=' expr ';'                       {}
           |return expr ';'                       {}
           |';'                                   {}
           |block                                 {}

expr : id                                         {}
      |literal                                    {}
      |expr bin_op expr                           {}
      |'!' expr                                   {}
      |'(' expr ')'                               {}

bin_op : arit_op                                  {} 
        |rel_op                                   {}
        |cond_op                                  {}

literal : integer_literal                         {}
	 |bool_literal                            {}

id : alpha alpha_numbers                          {}
