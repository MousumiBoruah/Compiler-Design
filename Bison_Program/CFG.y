%{
	#include<stdio.h>
	#include<string.h>

	int yylex();

	char buffer_1[10];
	char buffer_2[10];
	int flag = 0;

	void newLabel(){
    	sprintf(buffer_2, "L%d", flag++);
	}
	void newTemp(){
    	sprintf(buffer_1, "t%d", flag++);
	}
	

%}
%union{
    struct symbols{
		char* True;
		char* False;
		char* num;
		char* id;
		char* code;
		char* addr;
	}symbols;
}

%token ID NUM WHILE false true
%left '+'
%left '*'
%nonassoc '='
%type <symbols> ID E NUM A S B

%%
S : WHILE '(' B ')' '{' A '}' { 
                    char buffer_3[150];
					sprintf(buffer_3, "\nBegin: \n%s: %s\n GOTO: Begin\n%s:\n",
					$3.code, $3.True, $6.code, $3.False);
                    printf("%s\n", buffer_3); exit(0);}
  ;
B : true  { 
           newLabel();
           $$.True = strdup(buffer_2);
		   newLabel();
		   $$.False = strdup(buffer_2);
           char buffer_3[80];
		   sprintf(buffer_3, "if true GOTO %s \n GOTO %s",$$.True, $$.False);
		   $$.code = buffer_3;}
                       //printf("--> %s\n", buffer_3);}
  ;
A : ID '=' E ';' {
                    char buffer_3[150];
                    sprintf(buffer_3, "%s \n %s = %s", $3.code, $1.id, $3.addr);
					$$.code = buffer_3;
                    //printf("\n-->%s", $$.code);
					    }
  ;
E : E '*' E {char buffer_3[100];
  					newTemp();
  					$$.addr = strdup(buffer_1);
  					sprintf(buffer_3, "%s = %s * %s\n", $$.addr, $1.addr, $3.addr);
		           	$$.code = buffer_3; 
				   	//printf("%s\n", buffer_3);
			} 
  | ID {$$.addr = $1.id; $$.code = "";}
  | NUM {$$.addr = $1.num; $$.code = "";}
	  ;
  	
%%
#include "lex.yy.c"
int main() {
    printf("Enter the statement: \n");
    yyparse();

}
