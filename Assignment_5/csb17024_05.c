#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct grammar{
	char left;
	char right[15];
	char first_set[3];
	char follow_set[3];
}grammar;

grammar production[3];

int isterminal(char c){
	if(c == '+' || c == 'i')
		return(1);
	return(0);
}
int isepsilon(char *temp){
	int i;
	for (int i = 0; i < strlen(temp); ++i)
	{
		if(temp[i] == 'e')
			return 1;
	}
	return(0);
}

void FIRST(char NT){
	int i = 0,j =0;
	char ch;
	for(i = 0;i < 4;i++){
		if(production[i].left == NT){
			if(isterminal(production[i].right[0])){
				production[i].first_set[j++]=production[i].right[0];
			}
			if(isepsilon(production[i].right))
				production[i].first_set[j++]= 'e';
			else{
				ch = production[i].right[0];
				int k;
				for(k = i;k < 4;k++){
					if(production[k].left == ch){
						if(isterminal(production[k].right[0])){
							production[i].first_set[j++]=production[k].right[0];
						}	
					}
				}
			}
		}
	}
}
int check(char NT,char *temp){
	int j;
	for(int j = 0;j < strlen(temp);j++){
			if(temp[j] == NT){
				//printf("tum:%s %d\n",temp,j);
				return j;
			}
		}
	return 0;
}
char *find_first(char NT){
	for (int i = 0; i < 3; ++i)
	{
		if(NT == production[i].left){
			return (production[i].first_set);
		}
	}
	return ("Null");
}
void FOLLOW(char NT,int t){
	int i=0,j =0,current;
	char temp[7],first[7],buf;
	if(NT == 'S'){
		production[t].follow_set[j++]='$';
	}
	else{
		strcpy(temp,production[0].right);
		current = check(NT,temp);
		//printf("%d %c\n",current,temp[current]);
		if(temp[current+1] == '\0'){
			strcpy(production[t].follow_set,production[0].follow_set);
		}
		else {
			strcpy(first,find_first(temp[current+1]));
			if(isepsilon(first)){
				production[t].follow_set[j++] = first[0];
				strcat(production[t].follow_set,production[0].follow_set);
			}
		}
	} 
}
char (table[3][3])[9];
void create_table(){
	for(int i = 0;i < 3;i++){
		if(!isepsilon(production[i].first_set)){
			if(production[i].first_set[0] == 'i'){
				table[i][0][0] = production[i].left;
				strcat(table[i][0],"->");
				strcat(table[i][0],production[i].right);
			}
		}
		else if(isepsilon(production[i].first_set)){
			if(production[i].first_set[0] == '+'){
				table[i][1][0] = production[i].left;
				strcat(table[i][1],"->");
				char buffer[8];
				strcpy(buffer,production[i].right);
				buffer[strlen(buffer) - 2] = '\0';
				strcat(table[i][1],buffer);
			}
			if(production[i].follow_set[0] == '$'){
				table[i][2][0] = production[i].left;
				strcat(table[i][2],"->e");	
			}
		}
	}

}
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
	int j;
	production[0].left = 'S';
	strcpy(production[0].right,"AB");

	production[1].left = 'B';
	strcpy(production[1].right,"+AB|e");

	production[2].left = 'A';
	strcpy(production[2].right,"i");
	printf("------THE GRAMMAR is-----\n");
	for(j = 0;j < 3;j++){
		printf("%c->%s\n",production[j].left,production[j].right);
		FIRST(production[j].left);
	}
	
	for(j = 0;j < 3;j++){
		FOLLOW(production[j].left,j);
	}
	printf("e means epsilon\n\n");
	
	for(j = 0;j < 3;j++){
		printf("First(%c) = {%s}\t\tFollow(%c) = {%s}\n",production[j].left,production[j].first_set,production[j].left,production[j].follow_set);
	}
	printf("\n");
	
	create_table();
	print_table();
	
}