#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isFunction = false;

bool isDelimiter(char ch) {
    return strchr(" \t+-*/!|&;><=()[]{}", ch) != NULL;
}

bool isOperator(char ch) {
    return strchr("+-*/><=|&!", ch) != NULL;
}

bool isSeparator(char* str) {
    if (!strcmp(str, "(")) printf("<(, PARANTHESIS BEGIN>\n");
    else if (!strcmp(str, ")")) { isFunction = false; printf("<), PARANTHESIS END>\n"); }
    else if (!strcmp(str, "{")) printf("<{, BLOCK BEGIN>\n");
    else if (!strcmp(str, "}")) printf("<}, BLOCK END>\n");
    else if (!strcmp(str, ",")) printf("<,, SEPARATOR>\n");
    else if (!strcmp(str, ";")) printf("<;, DELIMITER>\n");
    else return false;

    return true;
}

bool isKeyword(char* str) {
    const char* keywords[] = {"if", "else", "while", "for", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "bool", "true", "false", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto"};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (!strcmp(str, keywords[i])) {
            printf("<%s, KEYWORD>\n", str);
            return true;
        }
    }

    return false;
}

bool isInteger(char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]) && !(i == 0 && str[i] == '-')) {
            return false;
        }
    }

    printf("<%s, INTEGER>\n", str);
    return true;
}

bool isRealNumber(char* str) {
    char* endptr;
    strtod(str, &endptr);

    if (*endptr == '\0') {
        printf("<%s, REAL NUMBER>\n", str);
        return true;
    }

    return false;
}

bool isCharLiteral(char* str) {
    if (str[0] == '\'' && str[strlen(str) - 1] == '\'') {
        printf("<%s, CHARACTER>\n", str);
        return true;
    }

    return false;
}

bool isStringLiteral(char* str) {
    if (str[0] == '\"' && str[strlen(str) - 1] == '\"') {
        printf("<%s, STRING LITERAL>\n", str);
        return true;
    }

    return false;
}

bool isIdentifier(char* str) {
    if (isdigit(str[0]) || isDelimiter(str[0]) || strchr(str, '.') != NULL) {
        return false;
    }

    for (int i = 0; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }

    return true;
}

bool isPreprocessorDirective(char* str) {
    if (str[0] == '#') {
        printf("<%s, PREPROCESSOR DIRECTIVE>\n", str);
        return true;
    }

    return false;
}

void parseToken(char* token) {
    if (isPreprocessorDirective(token) || !strcmp(token, "\n")) return;

    if (isOperator(token[0]) && isOperator(token[1])) {
        printf("<%s, COMPOUND OPERATOR>\n", token);
    } else if (isOperator(token[0])) {
        printf("<%s, OPERATOR>\n", token);
    } else if (isSeparator(token)) {
        // Handled in isSeparator function
    } else if (isKeyword(token)) {
        // Handled in isKeyword function
    } else if (isInteger(token)) {
        // Handled in isInteger function
    } else if (isRealNumber(token)) {
        // Handled in isRealNumber function
    } else if (isCharLiteral(token)) {
        // Handled in isCharLiteral function
    } else if (isStringLiteral(token)) {
        // Handled in isStringLiteral function
    } else if (isIdentifier(token)) {
        if (isFunction && token[strlen(token) - 1] == '(') {
            printf("<%s, FUNCTION>\n", token);
            isFunction = true;
        } else if (isFunction) {
            printf("<%s, ARGUMENT>\n", token);
        } else {
            printf("<%s, IDENTIFIER>\n", token);
        }
    } else if (strcmp(token, " ") && strcmp(token, "\t") && strcmp(token, "\n")) {
        printf("<%s, INVALID TOKEN>\n", token);
    }
}

void tokenize(char* line) {
    char* token = strtok(line, " \t\n");

    while (token != NULL) {
        parseToken(token);
        token = strtok(NULL, " \t\n");
    }
}

int main() {
    char filename[20];
    printf("Enter input filename: ");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File not found.\n");
        return 1;
    }

    char line[1000];

    while (fgets(line, sizeof(line), fp)) {
        tokenize(line);
    }

    fclose(fp);

    return 0;
}
