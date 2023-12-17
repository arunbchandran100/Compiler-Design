/*
	E ->E*E
	E->E+E
	E->id
*/	
#include<stdio.h>
#include<string.h>
char input[20];
char stack[50];
int i=0,top=0;
void push(char item)
{
	stack[top++]=item;
}	
int main()
{
	int len; 
	printf("Enter the input string\n");
	scanf("%s",input);
	len=strlen(input);
	input[len]='$';
	input[len+1]='\0';
	push('$');
	while(input[i]!='$')
	{
		if(input[i]=='i' && input[i+1]=='d')
		{
			printf("shift id\nreduce E->id\n");
			i=i+2;
			push('E');
			if(top>=3)
			{
				if(stack[top-1]=='E' && stack[top-3]=='E')
				{
					if(stack[top-2]=='*')
					{
						printf("reduce E->E*E\n");
						top=top-3;
						stack[top++]='E';
					}
					if(stack[top-2]=='+')
					{
						printf("reduce E->E+E\n");
						top=top-3;
						stack[top++]='E';
					}	
				}
			}
		}
		else
		{
			printf("shift %c\n",input[i]);
			push(input[i]);
			i++;
		}	
	}
	input[i]='\0';
	if(top==2)
	{
		if(stack[top-1]=='E')
		{
			printf("%s accepted\n",input);
		}
		else
		{
			printf("%s not accepted\n",input);
		}	
	}
	else
	{
		printf("%s not accepted\n",input);
	}			
}