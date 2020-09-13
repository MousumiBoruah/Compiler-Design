#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	FILE *f_input = fopen("input_file.txt","r");
	int line_number = 1;
	char temp[25];
	
	while(fgets(temp ,25 ,f_input) != NULL){
		printf("%d ",line_number++);
		printf("%s",temp);
	}
}