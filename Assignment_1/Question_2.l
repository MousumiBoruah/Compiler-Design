%{
	#include<stdio.h>
	#include "Token.h"
%}

%%
"return" {printf("<TOK_RETURN, %d>\n", TOK_RETURN);}
[0-9]+ {printf("<%s, TOK_NUM, %d>\n", yytext, TOK_NUM);}
[a-zA-Z][a-z_A-z_0-9]* {printf("<%s, TOK_ID, %d>\n", yytext, TOK_ID);}
"int" {printf("<TOK_INT, %d>\n", TOK_INT);}
"if" {printf("<TOK_IF, %d>\n", TOK_IF);}
"=" {printf("<TOK_ASSIGN, %d>\n", TOK_ASSIGN);}
[\n \t] {continue;}
"(" {printf("<TOK_R_RND_BRKT, %d>\n", TOK_R_RND_BRKT);}
")" {printf("<TOK_L_RND_BRKT, %d>\n", TOK_L_RND_BRKT);}
"{" {printf("<TOK_L_CRLY_BRKT, %d>\n",TOK_L_CRLY_BRKT );}
"}" {printf("<TOK_R_CRLY_BRKT, %d>\n",TOK_R_CRLY_BRKT);}
";" {printf("<TOK_SEMICOLON, %d>\n", TOK_SEMICOLON);}
"==" {printf("<TOK_EQU_COMP, %d>\n", TOK_EQU_COMP);}
"+=" {printf("<TOK_INCR_ASSIGN, %d>\n", TOK_INCR_ASSIGN);}
"+" {printf("<TOK_INCR, %d>\n", TOK_INCR);}
"else" {printf("<TOK_ELSE, %d>\n", TOK_ELSE);}
%%

int main(){
   
    yylex();
}
