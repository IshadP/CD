#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 100

char input[MAX];
int i = 0;

typedef struct {
    char production[100];
} ParsingTableEntry;

ParsingTableEntry parsingTable[5][6];

void fillParsingTable() {
    strcpy(parsingTable[0][0].production, "T E'");
    strcpy(parsingTable[0][5].production, "T E'");
    strcpy(parsingTable[1][1].production, "+ T E'");
    strcpy(parsingTable[1][5].production, "e");
    strcpy(parsingTable[2][0].production, "F T'");
    strcpy(parsingTable[2][5].production, "F T'");
    strcpy(parsingTable[3][2].production, "* F T'");
    strcpy(parsingTable[3][5].production, "e");
    strcpy(parsingTable[4][0].production, "( E )");
    strcpy(parsingTable[4][1].production, "id");
}

void printParsingTable() {
    printf("\nParsing Table:\n");
    printf("Non-Terminals \\ Terminals | i    +    *    (    )    $\n");
    char terminals[] = {'i', '+', '*', '(', ')', '$'};
    for (int i = 0; i < 5; i++) {
        printf(" %-18c |", 'E' + i);
        for (int j = 0; j < 6; j++) {
            printf(" %-8s", parsingTable[i][j].production[0] != '\0' ? parsingTable[i][j].production : "-");
        }
        printf("\n");
    }
}

void parseInput() {
    char stack[MAX];
    int top = 0;

    stack[top++] = '$';
    stack[top++] = 'E';
    
    while (stack[top - 1] != '$') {
        char currentSymbol = stack[top - 1];
        char currentInput = input[i];

        if (currentSymbol == currentInput) {
            top--;
            i++;
        } else if (currentSymbol >= 'A' && currentSymbol <= 'Z') {
            int row = currentSymbol - 'E';
            int col = currentInput == 'i' ? 0 :
                      currentInput == '+' ? 1 :
                      currentInput == '*' ? 2 :
                      currentInput == '(' ? 3 :
                      currentInput == ')' ? 4 :
                      currentInput == '$' ? 5 : -1;
            
            if (col != -1 && parsingTable[row][col].production[0] != '\0') {
                top--;
                for (int j = strlen(parsingTable[row][col].production) - 1; j >= 0; j--) {
                    if (parsingTable[row][col].production[j] != 'e') {
                        stack[top++] = parsingTable[row][col].production[j];
                    }
                }
            } else {
                printf("Syntax error at position %d\n", i);
                exit(1);
            }
        } else {
            printf("Syntax error at position %d\n", i);
            exit(1);
        }
    }

    if (input[i] == '$') {
        printf("Input string is valid.\n");
    } else {
        printf("Syntax error: Unexpected end of input.\n");
    }
}

int main() {
    printf("Enter expression (use 'i' for id, end with $): ");
    scanf("%s", input);

    fillParsingTable();
    printParsingTable();
    parseInput();

    return 0;
}
