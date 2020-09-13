#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	if(argc<2)
	{
		perror("Some arguments arent provided.\n");
		exit(1);
	}
	FILE *fp=fopen(argv[1], "rb");
	if(fp==NULL)
	{
		printf("Cant open this file.\n");
		exit(1);
	}
	char ch;
	if(argv[1][strlen(argv[1])-3]=='b')
	{
		while(1)
		{
			fread(&ch, sizeof(ch), 1, fp);
			if(feof(fp))
				break;
			else if(ch=='\0')
			{
				printf("\\0:%.3o ", ch);
			}
			else
			{
				/*if(ch >= '0' || ch<='9')
				{
					printf("%d:%o ", ch, ch);
				}
				else if(ch >= 'a' || ch <='z')
				{
					printf("%c:%o ", ch, ch);
				}*/
				printf("%c:%.3o ", ch, ch);
			}
		}
	}
	else
		printf("--Provided file isnt binary--");
	fclose(fp);
	return 0;
}