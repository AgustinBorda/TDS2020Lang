%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}

%option noyywrap
%option yylineno

digit [0-9]
alpha [a-zA-Z]
arith_op [+-]
rel_op [==]
cond_op [&&]
alpha_num {alpha}|{digit}

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

{arith_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
	return ARITH_OP;
}

{rel_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
	return REL_OP;
}

{cond_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
	return COND_OP;
}

[;()=]	{
	return *yytext;
}

"//./n"|"/*.*/"|"\s+"|"/t+"|"\n+" ;

. {
	yyerror(*yytext);
}
%%

void yyerror(char* symbol) {
	printf("Unexpected symbol \"%s\" on line %d\n",symbol,yylineno);
	exit(1);
}

int main(int argc, char* argv[]) {
	++argv,--argc;
	if (argc>0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	yyparse();
}

