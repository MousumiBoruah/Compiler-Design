#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*The grammar is
S -> A 
S -> (S * A) 
A  -> i*/ 

char stack[15],operation[25];
int top = 0,i = -1,flag = 0;
char input_buffer[15] = "((i*i)*i)$";
char lookahead;
char (table[2][5])[9] = {"S->(S*A)","-","S->A","-","-",
						"-","-","A->i","-","-"};
void print_grammar(){
	printf("\tS -> A\n\tS -> (S * A)\n\tA -> i\n\n");
}
void print_table(){
	printf("---------THE LL(1) PARSING TABLE FOR THE GRAMMAR---------\n\n");
	for(int column=0;column < 5;column++){
		if(column == 0){
			printf("\t(\t");
		}
		else if(column == 1){
			printf("\t)\t");
		}
		else if(column == 2){
			printf("\ti\t");
		}
		else if(column == 3){
			printf("\t*\t");
		}
		else{
			printf("\t$\t");
		}
	}
	printf("\n");
	printf("-----------------------------------------------------------------------------\n");
	for(int row = 0;row < 2;row++){
		if(row == 0){
			printf("S\t");
		}
		else{
			printf("A\t");
		}
		
		for(int column = 0;column < 5;column ++){
			printf("%s",table[row][column]);
			if(strlen(table[row][column]) < 8)
				printf("\t\t");
			else
				printf("\t");
		}
		printf("\n\n");
		printf("-----------------------------------------------------------------------------\n");
	}

}
char* search_table(){
	if(stack[top-1]== 'S' && lookahead == '('){
		return("(S*A)");
	}
	else if(stack[top-1]== 'S' && lookahead == 'i'){
		return("A");
	}
	else if(stack[top-1] == 'A' && lookahead == 'i'){
		return("i");
	}
	return("invalid");
}

int match(){
	if(lookahead == stack[top-1])
		return 1;
	return 0;
}

int isterminal(char lookahead){
	if(islower(lookahead) || lookahead == '(' || lookahead == ')' || lookahead == 'i' || lookahead == '*')
		return(1);
	return 0;
}

void pop(){
	operation[strlen(operation)] = ' ';
	operation[strlen(operation)] = stack[top-1];
	strcat(operation," Popped");
	//printf("%s\n",operation);
	top = top - 1;
}

void push(char *buffer){
	int i = 0; 
	char temp[20];
	strcpy(operation,buffer);
	strcat(operation," Pushed");
	//printf("%s\n",operation);
	for(i = strlen(buffer)-1;i >= 0;i--){
		stack[top++] = buffer[i];
	}
}

void parse(){
	int temp = 0,k = 1;
	char buffer[6];
	while(k){
		memset(operation,'\0',strlen(operation));
		if(temp == 0)
		 	lookahead = input_buffer[++i];
		if(temp == 1)
			lookahead = input_buffer[i];
		if(stack[top-1] == '$'){
			if(lookahead == '$'){
				printf("The String is Valid\n");
				flag = 1;
			}
			break;
		}
		if(k == strlen(input_buffer)+1)
		 	break;	
		if(isupper(stack[top-1]) && isterminal(lookahead)){
			strcpy(buffer,search_table());
			pop();
			push(buffer);
			temp = 1;
		}
		if(isterminal(stack[top-1]) && isterminal(lookahead)){
			if(match()){
				pop();
				temp = 0;
			}
			else{
				break;
			}
		}
		printf("\t%d\t",k++);
		for (int j = 0; j < top; j++){
			printf("%c",stack[j]);
		}
		int count = 0;
		if(top < 8)
			printf("\t\t\t");
		else
			printf("\t\t");
		for (int j = i+1; j < strlen(input_buffer); ++j){
			printf("%c",input_buffer[j]);
			count++;
		}
		if(count < 8){
			printf("\t\t%s\n",operation);
		}
		else
			printf("\t%s\n",operation);
		printf("\t\n");
	
	}
}

int main(){
	printf("The grammar is\n");
	print_grammar();
	print_table();
	stack[top++] = '$';
	stack[top++] = 'S';
	printf("\nThe input string is = %s\n",input_buffer);
	printf("\nIteration\tStack\t\t\tInput_Buffer\tOperation\n");
	printf("\t0\t");
	for (int j = 0; j < top; j++){
		printf("%c",stack[j]);
	}
	printf("\t\t\t");
	printf("%s\n",input_buffer);
	parse();
	if(flag == 0){
		printf("The String is not valid\n");
	}
}
