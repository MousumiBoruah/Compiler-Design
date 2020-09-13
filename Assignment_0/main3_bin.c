#include<stdio.h>
#include<stdlib.h>
int main(int argc, char * argv[])
{
	FILE *fp=fopen(argv[1], "wb");
	if(fp==NULL)
	{
		perror("FOPEN error:");
		exit(1);
	}
	char name[21];
	int roll, i=0;
	while(i<10)
	{
		printf("Enter the name and roll no of the student %d:", (i+1));
		scanf("%s %d", name, &roll);
		/*printf("Enter the roll no of the student %d:", (i+1));
		scanf("%d", &roll);*/
		fwrite(name, sizeof(name), 1, fp);
		fwrite(&roll, sizeof(roll), 1, fp);
		i++;
	}
}