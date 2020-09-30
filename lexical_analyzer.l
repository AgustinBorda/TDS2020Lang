%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "syntax_analyzer.tab.h"

%}

%option noyywrap
%option yylineno

digit [0-9]
alpha [a-zA-Z]
cond_op [&&]
alpha_num {alpha}|{digit}|[_-]

%%

"void" {
	return VOID;
}

"return" {
	return RETURN;
}

"extern" {
 	return EXTERN;
}

"integer" {
	return TYPE_INTEGER;
}

"bool" {
	return TYPE_BOOL;
}

"true"|"false" {
	if(strcmp(yytext,"true")==0) {
		yylval.i = 1;
        }
        else {
        	yylval.i = 0;
        }
        return BOOL_LITERAL;
}

{alpha}{alpha_num}* {
        yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.s,yytext);
        return ID;
}

{digit}+ {
	yylval.i = atoi(yytext);
	return INTEGER_LITERAL;
}

"=" {
	return ASIG_OP;
}

"+" {
	return PLUS_OP;
}

"-" {
	return MINUS_OP;
}

"*" {
	return MULT_OP;
}

"==" {
	return EQ_OP;
}

"&&" {
	return AND_OP;
}

"!" {
	return NOT_OP;
}

[;(),{}]	{
	return *yytext;
}

"//".*"\n"|"\s"+|"/t"+|"\n"+|"/*"[^*]*|[*]*"*/" ;

. { 
//	printf("%s\n",yytext);
	//lex_error(yytext);
}

%%

void lex_error(char* msg) {
	printf("Unexpected symbol \" %s \" on line %d\n",msg,yylineno);
	exit(1);
}

void yyerror() {
	printf("Syntax error on line %d\n",yylineno);
}

int main(int argc, char* argv[]) {
	++argv,--argc;
	if (argc>0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	yyparse();
}

