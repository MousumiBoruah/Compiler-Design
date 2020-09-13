#include<stdlib.h>
#include<stdio.h>
#include <string.h>

int main(int argc,char *argv[ ]){
	
	FILE *input_file = fopen(argv[1],"rb");
	char buffer;
	while(1){
		if(feof(input_file)){
			break;
		}
		fread(&buffer,sizeof(buffer),1,input_file);
		if(buffer >= ':' && buffer <= '}'){
				printf("%c ",buffer);
		}
	}
}