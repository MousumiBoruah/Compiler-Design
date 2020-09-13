#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct grammar{
	char left;
	char right[15];
}grammar;

grammar production[4];
char string[15],terminal[15],non_terminal[6],tem[5];

char *LEADING(char c){
	int i = 0,j = 0,k = 0,l = 0;
	char t[2],buffer;
	for(i = 0;i < 4;i++){
		if(production[i].left == c){
			strcpy(string,production[i].right);
			for(j = 0;j < strlen(string);j++){
				if(islower(string[j]) || string[j] == ')' || string[j] == '(' || string[j] == '<' || string[j] == ';' || string[j] == '=' || string[j] == '/'){
					tem[k++] = string[j];
					tem[k++] = '\0';
					return(tem);
				}
				else{
					buffer = string[++j];
					strcpy(t,LEADING(string[--j]));
					tem[k++] = t[0];
					tem[k++] = buffer;
					tem[k++] = '\0';
					return(tem);
				}
			}

		}
	}
}
char *TRAILING(char c){
	int i = 0,j = 0,k = 0,l = 0;
	char t[2],buffer;
	for(i = 0;i < 4;i++){
		if(production[i].left == c){
			strcpy(string,production[i].right);
			for(j = strlen(string)-1;j > 0;j--){
				if(islower(string[j]) || string[j] == ')' || string[j] == '(' || string[j] == '<' || string[j] == ';' || string[j] == '=' || string[j] == '/'){
					tem[k++] = string[j];
					tem[k++] = '\0';
					return(tem);
				}
				else{
					buffer = string[--j];
					strcpy(t,TRAILING(string[++j]));
					tem[k++] = t[0];
					tem[k++] = buffer;
					tem[k++] = '\0';
					return(tem);
				}
			}

		}
	}	
}

int main(){
	int i = 0;
	production[0].left = 'A';
	strcpy(production[0].right,"w(C)bSe");

	production[1].left = 'C';
	strcpy(production[1].right,"i<n");

	production[2].left = 'S';
	strcpy(production[2].right,"E;");

	production[3].left = 'E';
	strcpy(production[3].right,"i=i/n");
    
    printf("THE OPERATOR GRAMMAR IS:\n");
	for(i = 0;i < 4;i++){
		printf("%c->%s\n",production[i].left,production[i].right);
	}
	printf("\n");
	for(i = 0;i < 4;i++){
		printf("LEADING(%c) = {%s}",production[i].left,LEADING(production[i].left));
		printf(" \tTRAILING(%c) = {%s}\n",production[i].left,TRAILING(production[i].left));
	}
}