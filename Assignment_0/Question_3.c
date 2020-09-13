#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	char name[25],file_name[20],roll_num[25];
	int count = 0,file_name_length = 0,roll_no;
	printf("Enter the name of the file with extension\n");
	scanf("%s",file_name);
	file_name_length = strlen(file_name);
	if(file_name[file_name_length - 3] == 't'){
		FILE *input_file = fopen(file_name,"w");
		while(count < 10){
			printf("Enter the name and roll_no of %d student\n",count++);
			scanf("%s %d",name , &roll_no);
			fputs(name,input_file);
			fputc('\t',input_file);
			//fputs(roll_no,input_file);
			fprintf(input_file,"%d",roll_no);
			fputc('\n',input_file);
		}
	}
	else {
		FILE *input_file = fopen(file_name,"wb");
		while(count < 10){
			printf("Enter the name and roll_no of %d student\n",++count);
			scanf("%s %d",name , &roll_no);
			fwrite(name,sizeof(name),1,input_file);
			fwrite(&roll_no,sizeof(roll_no),1,input_file);

		}
	}
}