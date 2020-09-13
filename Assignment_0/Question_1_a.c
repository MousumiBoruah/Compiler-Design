#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	FILE *f_input = fopen("input_file.txt","r");
	int line_number = 1;
	char temp;
	printf("%d ",line_number++);
	while(!feof(f_input)){
		
		if((temp = fgetc(f_input)) != '\n'){
			printf("%c",temp);
		}
		else{
			printf("\n");
			printf("%d ",line_number++);
		}
	}
}