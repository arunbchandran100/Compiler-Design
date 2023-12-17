%{
int nlines, nwords, nchars;
%}

%%

\n { nchars++; nlines++; }
 
[^ \n\t]+ { nwords++, nchars = nchars + yyleng; }

. { nchars++; }

%%

int yywrap(void)  
{
	return 1;
}

int main() 
{
	char filename[50];
	printf("Enter filename: ");
	scanf("%s", filename);
	yyin = fopen(filename, "r");
	
	if(!yyin) {
		printf("Could not open file\n");
		exit(1);
	}
	
	yylex();
	printf("Lines = %d\nWords = %d\nChars = %d\n", nlines, nwords, nchars);
	
	return 0;
}
