#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct grammar{
	char left;
	char right[15];
}grammar;

grammar production[4];

int i = 0,check = 0;
char input[] = "w (a<7) b a=a/7; e";

int C(){
	if(isalpha(input[i++])){
		if(input[i++] == '<'){
			if(input[i] == ' ')
				i++;
			if(isdigit(input[i++])){
				//printf("True:C\n");
				return 1;
			}
		}
	}
	//printf("False:C\n");
	return 0;
}
int S(){
	if(isalpha(input[i++])){
		if(input[i++] == '='){
			if(isalpha(input[i++])){
				if(input[i++] == '/'){
					if(input[i] == ' ')
						i++;
					if(isdigit(input[i++])){
						if(input[i++] == ';'){
							//printf("True:S\n");
							return 1;
						}
					}
				}
			}
		}
	}
	//printf("False:S\n");
	return 0;
}
int A(){
	if(input[i++] == 'w'){
		if(input[i] == ' ')
			i++;
		if(input[i++] == '('){
			check = C();
			if(check == 1){
				if(input[i++] == ')'){
					if(input[i] == ' ')
						i++;
					if(input[i++] == 'b'){
						if(input[i] == ' ')
							i++;
						check = S();
						if(check == 1){
							if(input[i] == ' ')
								i++;
							if(input[i++] == 'e'){
								//printf("True:A\n");
								return 1;
							}
						}
					}
				}
			}
		}		
	}
	//printf("False:A\n");
	return 0;
}


int main(){
	int j = 0;
	production[0].left = 'A';
	strcpy(production[0].right,"w(C)bSe");

	production[1].left = 'C';
	strcpy(production[1].right,"i<n");

	production[2].left = 'S';
	strcpy(production[2].right,"i=i/n;");
	printf("The Grammar is\n");
	for(j = 0;j < 3;j++){
		printf("%c->%s\n",production[j].left,production[j].right);
	}
	check = A();
	if(check == 1){
		printf("\nThe input string is %s\n",input);
		printf("\nThe string is valid\n");
	}
	else{
		printf("\nThe input string is %s\n",input);
		printf("\nThe string is not valid\n");
	}
}