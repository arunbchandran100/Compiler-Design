%{

#include <stdio.h>

int flag = 0;
    
%}

%token NUMBER

%left '+' '-'

%left '*' '/' '%'

%left '(' ')'

%%

ArithmeticExpression: E{

         printf("\nResult = %d\n",$$);

         return 0;

        };

E:E'+'E {$$=$1+$3;}

 |E'-'E {$$=$1-$3;}

 |E'*'E {$$=$1*$3;}

 |E'/'E {$$=$1/$3;}

 |E'%'E {$$=$1%$3;}

 |'('E')' {$$=$2;}

 | NUMBER {$$=$1;}

;

%%

void main() {

	printf("Enter arithmetic expression [ + - * / % ( ) ]:\n");

	yyparse();

	if(flag == 0)
		printf("\nExpression is valid.\n");
}

void yyerror() {
	
	printf("\nExpression is invalid!\n");
	
	flag = 1;
	
}
