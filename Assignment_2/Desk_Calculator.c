#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define sub 0
#define add 1
#define mul 2
#define div 3
//1:- Takes precedence from
//0:- Yields precedence to
int table[4][4] = {
		{1 , 1 , 0 , 0},
		{1 , 1 , 0 , 0},
		{1 , 1 , 1 , 1},
		{1 , 1 , 1 , 1}
};

typedef struct stack_record{
	char type;
	int value;
}stack_rec;

stack_rec stack[10];
int top = 1,prev = -1;


void push(stack_rec data){
		stack[top].type = data.type;
		stack[top++].value = data.value;
}
int pop(void){
	return(stack[--top].value);
}
int operation(){
	int opr_1 = pop();
	int operator = pop();
	int opr_2 = pop();
	if(operator == 0){

		return(opr_2 - opr_1);
	}
	else if(operator == 1){
		return(opr_2 + opr_1);
	}
	else if(operator == 2){
		return(opr_1 * opr_2);
	}
	else if(operator == 3){
		return(opr_2 / opr_1);
	}
}
void parsing(char *buffer){
	char operand[5];
	stack_rec data,temp;
	int i ,result;
	for(i = 0;i < strlen(buffer);i++){
		if(!isdigit(buffer[i])){
			if(buffer[i] == '+'){
				data.type = 'O';
				data.value = add;
				while(1){
					if(prev == -1){
						push(data);
						prev = add;
						break;
					}
					else if(table[prev][data.value] == 0 || stack[top].value == -1){
						push(data);
						prev = add;
						break;
					}
					else if(table[prev][data.value] == 1){
						result = operation();
						if(stack[top-1].value != -1)
							prev = stack[top-1].value;
						else if(stack[top-1].value == -1)
							prev = -1;
						temp.type = 'R';
		    			temp.value = result;
		    			push(temp);
					}
				}
			}
			 else if(buffer[i] == '-'){
				data.type = 'O';
				data.value = sub;
			while(1){
					if(prev == -1){
						push(data);
						prev = sub;
						break;
					}
					else if(table[prev][data.value] == 0 || stack[top].value == -1){
						push(data);
						prev = sub;
						break;
					}
					else if(table[prev][data.value] == 1){
						result = operation();
						if(stack[top-1].value != -1)
							prev = stack[top-1].value;
						else if(stack[top-1].value == -1)
							prev = -1;
						temp.type = 'R';
		    			temp.value = result;
		    			push(temp);
					}
				}
			}
			else if(buffer[i] == '*'){
				data.type = 'O';
				data.value = mul;
				while(1){
					if(prev == -1){
						push(data);
						prev = mul;
						break;
					}
					else if(table[prev][data.value] == 0 || stack[top].value == -1){
						push(data);
						prev = mul;
						break;
					}
					else if(table[prev][data.value] == 1){
						result = operation();
						if(stack[top-1].value != -1)
							prev = stack[top-1].value;
						else if(stack[top-1].value == -1)
							prev = -1;
						temp.type = 'R';
		    			temp.value = result;
		    			push(temp);
					}
				}
			}
			else if(buffer[i] == '/'){
				data.type = 'O';
				data.value = div;
				while(1){
					if(prev == -1){
						push(data);
						data.value = div;
						prev = div;
						break;
					}
					else if(table[prev][data.value] == 0 || stack[top].value == -1){
						push(data);
						prev = div;
						break;
					}
					else if(table[prev][data.value] == 1){
						result = operation();
						if(stack[top-1].value != -1)
							prev = stack[top-1].value;
						else if(stack[top-1].value == -1)
							prev = -1;
						temp.type = 'R';
		    			temp.value = result;
		    			push(temp);
					}
				}
			}
		}
		else if(isdigit(buffer[i])){
			int j = 0;
			operand[j] = buffer[i];
			while(isdigit(buffer[++i])){
	    		operand[++j] = buffer[i];
	    	}
	    	i--;
	    	operand[j+1] = '\0';
	    	data.type = 'R';
	    	data.value = atoi(operand);
	    	push(data);
		}
	}
	while(top != 0){
		result = operation();
		temp.type = 'R';
		temp.value = result;
		push(temp);
	}
	printf("Final_result=%d\n",result);
}
void print(){
	int i = 0;
	for(i = 0;i < top;i++){
		printf("%c %d\n",stack[i].type, stack[i].value);
	}
}
int main(){
	char buffer[30];
	stack[0].value = -1;
	printf("Enter the Arithmetic Expression\n");
	fgets(buffer , 30 ,stdin);
	parsing(buffer);
	print();
}