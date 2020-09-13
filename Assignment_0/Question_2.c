#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char temp,(buffer[5][10])[25],str[20],file_name[20];
	int row = 0,column = 0,i = 0,field = 0,flag = 0,flag_1 = 0;
	printf("Enter the file name and field number\n");
	scanf("%s %d",file_name,&field);
	FILE *f_input = fopen(file_name,"r");
	
	while(1){
		if(feof(f_input)){
			str[i] = '\0';
			strcpy(buffer[row][column],str);
			break;
		}
		if((temp = fgetc(f_input)) != '\n'){
			if(temp != ' '){
				str[i++] = temp;
				flag = 0;flag_1 = 0;
			}
			else{
				if(flag == 0 && flag_1 == 0){
					str[i] = '\0';
					strcpy(buffer[row][column],str);
					column++;i = 0;flag = 1;
				}
			}
		}
		else if(temp == '\n'){
				str[i] = '\0';
				strcpy(buffer[row][column],str);
				row++; column = 0;i = 0;flag_1 = 1;
			
		}
	}
	for(row = 0; row < 5;row++){
		printf("%s\n",buffer[row][field-1]);
	}
}