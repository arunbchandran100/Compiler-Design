%{
int i;
%}

%%

[a-z A-Z]* {
	for(i = 0; i <= yyleng; i++) {
		if((yytext[i]=='a') && (yytext[i+1]=='b') && (yytext[i+2]=='c')) {
			yytext[i]='A';
			yytext[i+1]='B';
			yytext[i+2]='C';
		}
	}

	printf("Output string: %s\n", yytext);
}
[\t]* return 0;
.* {ECHO;}
\n {printf("\nEnter string: ");}

%%

void main() {
	printf("Enter string: ");
	yylex();
}

int yywrap() {
	return 1;
}
