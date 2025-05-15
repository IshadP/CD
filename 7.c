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
    // E
    strcpy(parsingTable[0][0].production, "T Q");
    strcpy(parsingTable[0][3].production, "T Q");

    // E'
    strcpy(parsingTable[1][1].production, "+ T Q");
    strcpy(parsingTable[1][4].production, "e");
    strcpy(parsingTable[1][5].production, "e");

    // T
    strcpy(parsingTable[2][0].production, "F R");
    strcpy(parsingTable[2][3].production, "F R");

    // T'
    strcpy(parsingTable[3][1].production, "e");
    strcpy(parsingTable[3][2].production, "* F R");
    strcpy(parsingTable[3][4].production, "e");
    strcpy(parsingTable[3][5].production, "e");

    // F
    strcpy(parsingTable[4][0].production, "i");
    strcpy(parsingTable[4][3].production, "( E )");
}

void printParsingTable() {
    printf("\nParsing Table:\n");
    printf("Non-Terminals \\ Terminals | i     +     *     (     )     $\n");

    char nonTerminals[] = {'E', 'Q', 'T', 'R', 'F'};
    for (int row = 0; row < 5; row++) {
        printf(" %-23c |", nonTerminals[row]);
        for (int col = 0; col < 6; col++) {
            if (parsingTable[row][col].production[0] != '\0')
                printf(" %-6s ", parsingTable[row][col].production);
            else
                printf(" %-6s ", "-");
        }
        printf("\n");
    }
}

int getRow(char nonTerminal) {
    switch (nonTerminal) {
        case 'E': return 0;
        case 'Q': return 1;
        case 'T': return 2;
        case 'R': return 3;
        case 'F': return 4;
        default: return -1;
    }
}

int getCol(char terminal) {
    switch (terminal) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

void pushProduction(char *production, char stack[], int *top) {
    int len = strlen(production);
    for (int j = len - 1; j >= 0; j--) {
        char c = production[j];
        if (c == ' ' || c == 'e') continue;
        stack[(*top)++] = c;
    }
}

void parseInput() {
    char stack[MAX];
    int top = 0;

    stack[top++] = '$';
    stack[top++] = 'E';

    i = 0;
    char currentInput = input[i];

    while (top > 0) {
        char stackTop = stack[top - 1];

        if (stackTop == currentInput) {
            top--;
            i++;
            if (input[i] == '\0')
                currentInput = '$';
            else
                currentInput = input[i];
        }
        else if (stackTop >= 'A' && stackTop <= 'Z') {
            int row = getRow(stackTop);
            int col = getCol(currentInput);
            if (row == -1 || col == -1) {
                printf("Syntax error at position %d: unexpected symbol '%c'\n", i, currentInput);
                exit(1);
            }

            char *production = parsingTable[row][col].production;
            if (production[0] == '\0') {
                printf("Syntax error at position %d: no production for %c with input '%c'\n", i, stackTop, currentInput);
                exit(1);
            }

            top--;
            pushProduction(production, stack, &top);
        }
        else {
            printf("Syntax error at position %d: unexpected symbol '%c'\n", i, currentInput);
            exit(1);
        }
    }

    if (currentInput == '$') {
        printf("Input string is valid.\n");
    } else {
        printf("Syntax error: input not fully parsed, stopped at '%c'\n", currentInput);
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
