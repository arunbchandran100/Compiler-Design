#include<stdio.h>
#include<string.h>
struct statement
{
	char lhs[5];
	char rhs[3];
}st[20];	
int main()
{
	int n;
	printf("Enter no. of statement:");
	scanf("%d",&n);
	printf("Enter statements\n");
	for(int i=0;i<n;i++)
	{
		scanf(" %s = %s",st[i].lhs,st[i].rhs);
	}
	for(int i=0;i<n;i++)
	{
		if(strlen(st[i].rhs)==1)
		{
			printf("MOV AX,%s\n",st[i].rhs);
			printf("MOV %s,AX\n",st[i].lhs);
		}
		else
		{
			printf("MOV AX,%c\n",st[i].rhs[0]);		
			printf("MOV BX,%c\n",st[i].rhs[2]);
			if(st[i].rhs[1]=='+')
			{
				printf("ADD AX,BX\n");
				printf("MOV %s,AX\n",st[i].lhs);
			}
			else if(st[i].rhs[1]=='-')
			{
				printf("SUB AX,BX\n");
				printf("MOV %s,AX\n",st[i].lhs);
			}
			else if(st[i].rhs[1]=='*')
			{
				printf("MUL AX,BX\n");
				printf("MOV %s,AX\n",st[i].lhs);
			}
			else if(st[i].rhs[1]=='/')
			{
				printf("DIV AX,BX\n");
				printf("MOV %s,AX\n",st[i].lhs);
			}
		}	
	}
}