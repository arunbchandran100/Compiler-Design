%{
#include <string.h>
int comment = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%

\/\/.* {printf("\n%s is a COMMENT", yytext);}

\/\* {comment = 1; printf("\n"); ECHO; printf("\nCOMMENT BEGINS");}
\*\/ {comment = 0; printf("\nCOMMENT ENDS\n"); ECHO;}

#.* {printf("\n%s is a PREPROCESSOR DIRECTIVE",yytext);}

int |
float |
char |
double |
while |
for |
struct |
typedef |
do |
if |
break |
continue |
void |
switch |
return |
else |
goto {if(!comment) printf("\n%s is a KEYWORD", yytext);}

{identifier}\( {yytext[strlen(yytext) - 1] = '\0'; if(!comment) printf("\n%s is a FUNCTION\n\n( is an OPENING PARANTHESIS", yytext);}

\{ {if(!comment) {printf("\n\n"); ECHO; printf("\nBLOCK BEGINS");}}

\} {if(!comment) {printf("\nBLOCK ENDS\n"); ECHO;}}

{identifier}(\[[0-9]*\])? {if(!comment) printf("\n%s is an IDENTIFIER", yytext);}

\".*\" {if(!comment) printf("\n%s is a STRING", yytext);}

[0-9]+ {if(!comment) printf("\n%s is a NUMBER", yytext);}

\( {if(!comment) printf("\n%s is an OPENING PARANTHESIS", yytext);}

\) {if(!comment) printf("\n%s is a CLOSING PARANTHESIS", yytext);}

\)(\:)? {if(!comment) printf("\n"); if(!comment) ECHO; if(!comment) printf("\n");}

= {if(!comment) printf("\n%s is an ASSIGNMENT OPERATOR", yytext);}

\<= |
\>= |
\< |
== |
\> {if(!comment) printf("\n%s is a RELATIONAL OPERATOR", yytext);}

, {if(!comment) printf("\n%s is a SEPARATOR", yytext);}

; {if(!comment) printf("\n%s is a DELIMITER", yytext);}

[+-/*%] {if(!comment) printf("\n%s is an ARITHMETIC OPERATOR", yytext);}

[|&\^] {if(!comment) printf("\n%s is a BITWISE OPERATOR", yytext);}

! |
&& |
\|\| {if(!comment) printf("\n%s is a LOGICAL OPERATOR", yytext);}
 
%%

int main() {
	char filename[50];
	
	printf("Enter filename: ");
	scanf("%s", filename);
	
	FILE *file;
	file = fopen(filename,"r");
	
	if(!file) {
		printf("Could not open the file\n");
		exit(0);
	}
	
	yyin = file;
	yylex();
	printf("\n");
	return(0);
}

int yywrap() {
	return(1);
}
