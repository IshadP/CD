

%{
#include <stdio.h>
#include <string.h>
//does not have function detection
int isKeyword(const char *word) {
    const char *keywords[] = {
        "int", "float", "if", "else", "while", "for", "return", "void", "char", "double", "do", "switch", "case", "break"
    };
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}
%}

IDENTIFIER     [a-zA-Z_][a-zA-Z0-9_]*
NUMBER         [0-9]+(\.[0-9]+)?
OPERATOR       \+\+|--|==|!=|>=|<=|=|<|>|\+|-|\*|/|%|&&|\|\||!
WHITESPACE     [ \t\n\r]+

%%

"//".*                       { printf("Single-line Comment: %s\n", yytext); }
"/*"([^*]|\*+[^*/])*\*+\/    { printf("Multi-line Comment: %s\n", yytext); }

{NUMBER}                    { printf("Number: %s\n", yytext); }
"++"|"--"|"=="|"!="|">="|"<="|"="|"<"|">"|"+"|"-"|"*"|"/"|"%"|"&&"|"||"|"!"  {
    printf("Operator: %s\n", yytext);
}

{IDENTIFIER}                {
                                if (isKeyword(yytext))
                                    printf("Keyword: %s\n", yytext);
                                else
                                    printf("Identifier: %s\n", yytext);
                            }

[{}()\[\];,]                { printf("Punctuation: %s\n", yytext); }

{WHITESPACE}                { /* Ignore */ }

.                           { printf("Unknown character: %s\n", yytext); }

%%

int main() {
    printf("Enter code (Ctrl+D to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
