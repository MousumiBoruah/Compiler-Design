#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*The grammar is
S->AB
B->+AB|e
A->i*/ 

char stack[15];
char *input_buffer[15];
char lookahead;
char (table[3][3])[9] = {"S->AB","-","-",
						"-","B->+AB","B->e",
						"A->i","-","-"};
void print_table(){
	printf("---------THE LL(1) PARSING TABLE FOR THE GRAMMAR---------\n\n");
	for(int column=0;column < 3;column++){
		if(column == 0){
			printf("\ti\t");
		}
		else if(column == 1){
			printf("\t+\t");
		}
		else{
			printf("\t$\t");
		}
	}
	printf("\n");
	printf("-----------------------------------------------\n");
	for(int row = 0;row < 3;row++){
		if(row == 0){
			printf("S\t");
		}
		else if(row == 1){
			printf("B\t");
		}
		else{
			printf("A\t");
		}
		
		for(int column = 0;column < 3;column ++){
			printf("%s\t\t",table[row][column]);
		}
		printf("\n\n");
		printf("-----------------------------------------------\n");
	}

}

int main(){
	print_table();
}
