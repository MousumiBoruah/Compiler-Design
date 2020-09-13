%{
	#include <stdio.h>
	#include <string.h>
%}

NUM [0-9]+
ID [a-z][a-z0-9]*

%%
"while" {return WHILE;}
"=="    {return EQ_COMP;}
{ID}    {yylval.symbols.id = strdup(yytext); return ID; }
{NUM}   {yylval.symbols.num = strdup(yytext); return NUM;}
[=+*,{}();] {return *yytext;}
[\t\n]+ ;
%%