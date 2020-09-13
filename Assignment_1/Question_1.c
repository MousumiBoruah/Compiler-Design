#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Token.h"
#include<ctype.h>

char token_buffer[10];

int lexical_analyser(FILE *f_source){
    while(!feof(f_source)){
		char ch = fgetc(f_source);
		char ch_1;
		if(ch == ';') 
			printf("<TOK_SEMICOLON,%d>\n",TOK_SEMICOLON);
		else if(ch == ',') 
			printf("<TOK_COMMA,%d>\n",TOK_COMMA);
		else if(ch == '+'){
			ch_1 = fgetc(f_source);
			if(ch_1 == '+') 
				printf("<TOK_INCR,%d>\n",TOK_INCR);
			else if(ch_1 == '=') 
				printf("<TOK_INCR_ASSIGN,%d>\n",TOK_INCR_ASSIGN);
			else{ 
				ungetc(ch_1,f_source);
				printf("<TOK_PLUS,%d>\n",TOK_PLUS);
			}
		}
		else if(ch == '='){
			ch_1 = fgetc(f_source);
			if(ch_1 == '=') 
				printf("<TOK_EQU_COMP,%d>\n",TOK_EQU_COMP);
			else {
				ungetc(ch_1,f_source);
				printf("<TOK_ASSIGN,%d>\n",TOK_ASSIGN);
			}
		}
		else if(ch == ')'){
			printf("<TOK_R_RND_BRKT,%d>\n",TOK_R_RND_BRKT);
		}
		else if(ch == '('){
			printf("<TOK_L_RND_BRKT,%d>\n",TOK_L_RND_BRKT);
		}
	 	else if(isalpha(ch)){
			int i = 0;
	    	token_buffer[i] = ch;
	    	while((isalnum(ch = fgetc(f_source)))){
	    		token_buffer[++i] = ch;
	    	}
	    	token_buffer[++i] = '\0';
	    	if(strcmp(token_buffer,"if") == 0){
	    		printf("<TOK_IF,%d>\n",TOK_IF);
	    	}
	    	else if(strcmp(token_buffer,"return") == 0){
	    		printf("<TOK_RETURN,%d>\n",TOK_RETURN);
	    	}
	    	else if(strcmp(token_buffer,"else") == 0){
	    		printf("<TOK_ELSE,%d>\n",TOK_ELSE);
	    	}
	    	else if(strcmp(token_buffer,"int") == 0){
	    		printf("<TOK_INT,%d>\n",TOK_INT);
	    	}
	    	else{
	    		printf("<%s,TOK_ID,%d>\n",token_buffer,TOK_ID);
	    	}
	    }
	    else if(isdigit(ch)){
	    	int i = 0;
	    	token_buffer[i] = ch;
	    	while(isdigit(ch = fgetc(f_source))){
	    		token_buffer[++i] = ch;
	    	}
	    	token_buffer[++i] = '\0';
	    	ungetc(ch,f_source);
	    	printf("<%s,TOK_NUM,%d>\n",token_buffer,TOK_NUM);
		}
		else if(ch == '{'){
	    	printf("<TOK_L_CRLY_BRKT,%d>\n",TOK_L_CRLY_BRKT);
	    }
	    else if(ch == '}'){
	    	printf("<TOK_R_CRLY_BRKT,%d>\n",TOK_L_CRLY_BRKT);
	    }
	    else if(ch == '>'){
	    	printf("<TOK_GRTR_COMP,%d>\n",TOK_GRTR_COMP);
	    }
	    else if(ch == '<'){
	    	printf("<TOK_LESS_COMP,%d>\n",TOK_LESS_COMP);
	    }

	}
}
int main(int argc,char *argv[]){
	int token;
	FILE *f_source = fopen(argv[1],"r");
	lexical_analyser(f_source);
	
}
