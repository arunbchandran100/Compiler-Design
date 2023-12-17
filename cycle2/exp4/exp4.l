%{
#include <stdio.h>
int vow = 0, con = 0;
%}

%%

[aeiouAEIOU] {vow++;}
[a-zA-Z] {con++;}
\n {return 0;}
[^a-zA-Z] ;

%%

void main() {
	printf("Enter string: ");
	yylex();
	printf("Number of vowels = %d\n",vow);
	printf("Number of consonants = %d\n",con);
}

int yywrap()
{
	return 1;
}
