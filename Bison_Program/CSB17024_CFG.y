%{
	#include<stdio.h>
	#include<string.h>

	int yylex();
	void yyerror(char*);

	char buffer_1[10];
	int flag_1 = 0;

	void create_temp(){
    	sprintf(buffer_1, "t%d", flag_1++);
	}
	
%}

%union{
    struct symbols{
		char* label_true;
		char* label_false;
		char* num;
		char* id;
		char* three_AC;
		char* temp;
	}symbols;
}

%token ID NUM WHILE EQ_COMP
%type <symbols> ID E NUM A S B
%left '+'
%left '*'
%nonassoc '='


%%
S : WHILE '(' B ')' '{' A '}' {char buffer_2[150];
					sprintf(buffer_2,"\nbegin: \n%s%s:\n %s\n \tgoto begin\n%s:\n",
					$3.three_AC, $3.label_true, $6.three_AC, $3.label_false);
                    printf("%s\n", buffer_2);
                    }
   ;
B : E EQ_COMP E {
           			$$.label_true = strdup("B.true");
		       		$$.label_false = strdup("B.false");
                    char buffer_2[80];
		       		sprintf(buffer_2, "\tif %s == %s goto %s \n\tgoto %s\n",$1.temp, $3.temp, $$.label_true, $$.label_false);
		       		$$.three_AC = buffer_2;
                }
    ;
A : ID '=' E ';' {
                    char buffer_2[150];
                    sprintf(buffer_2, "\t%s \t%s = %s",$3.three_AC,$1.id, $3.temp);
					$$.three_AC = buffer_2;
				 }
	;
E : E '*' E {char buffer_2[100];
  					create_temp();
  					$$.temp = strdup(buffer_1);
  					sprintf(buffer_2, "%s = %s * %s\n", $$.temp, $1.temp, $3.temp);
		           	$$.three_AC = buffer_2; 
			} 
  | E '+' E {char buffer_2[100];
  					create_temp();
  					$$.temp = strdup(buffer_1);
  					sprintf(buffer_2, "%s = %s + %s\n", $$.temp, $1.temp, $3.temp);
		           	$$.three_AC = buffer_2; 
		   }
  | '(' E ')' {$$.temp = $2.temp;
  			   $$.three_AC = $2.three_AC;
  			  }
  | ID {$$.temp = $1.id; $$.three_AC = "";}
  | NUM {$$.temp = $1.num; $$.three_AC = "";}
	  ;
  	
%%
#include "lex.yy.c"
int main() {
    printf("Enter the statement: \n");
    yyparse();
}
