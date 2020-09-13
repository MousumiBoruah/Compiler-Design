#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){
	if(argc < 2){
		perror("Enter proper arguments\n");
	}
	FILE* f_input = fopen(argv[1],"rb");
	char buffer;
	int count = 0;
	while(1){
		if(feof(f_input)){
			printf("\n");
			break;
		}
		fread(&buffer, sizeof(buffer), 1,f_input);
		if((count % 16) == 0){
			printf("\n%.7o\t",count);
		}
		printf("%.3o\t",buffer);
		count++;
	}
}