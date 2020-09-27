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
	printf("VOID\n");
	return VOID;
}

"return" {
 	printf("RETURN\n");
	return RETURN;
}

"extern" {
	printf("EXTERN\n");
 	return EXTERN;
}

"integer" {
        printf("TYPE_INTEGER\n");
	return TYPE_INTEGER;
}

"bool" {
        printf("TYPE_BOOL\n");
	return TYPE_BOOL;
}

"true"|"false" {
	if(strcmp(yytext,"true")==0) {
        	printf("TRUE\n");
		yylval.i = 1;
        }
        else {
		printf("FALSE\n");
        	yylval.i = 0;
        }
        return BOOL_LITERAL;
}

{alpha}{alpha_num}* {
        yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.s,yytext);
        printf("ID\n");
        return ID;
}

{digit}+ {
	yylval.i = atoi(yytext);
        printf("INTEGER_LITERAL\n");
	return INTEGER_LITERAL;
}

{arith_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
        printf("ARITH_OP\n");
	return ARITH_OP;
}

{rel_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
        printf("REL_OP\n");
	return REL_OP;
}

{cond_op} {
	yylval.s=(char*) malloc(sizeof(yytext)*yyleng);
	strcpy(yylval.s,yytext);
        printf("COND_OP\n");
	return COND_OP;
}

[;()=]	{
	return *yytext;
}

"//./n"|"/*.*/"|"\s+"|"/t+"|"\n+" ;

%%


void yyerror() {
	printf("Unexpected symbol \"%s\" on line %d\n",yytext,yylineno);
}

int main(int argc, char* argv[]) {
	++argv,--argc;
	if (argc>0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	yyparse();
}

