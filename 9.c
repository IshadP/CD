#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define INPUT_SIZE 100

typedef struct {
    int state;
    char symbol;
} StackEntry;

StackEntry stack[STACK_SIZE];
int top = 0;

char input[INPUT_SIZE];
int ip = 0; 

const char *productions[] = {
    "E->E+T",
    "E->T",
    "T->T*F",
    "T->F",
    "F->(E)",
    "F->i"   
};


const int numProductions = 6;
int actionTable[12][6] = {
/*i   +    *    (    )    $  */
{ 5,  0,   0,   4,   0,   0 },
{ 0,  6,   0,   0,   0, 999 },
{ 0, -2,   7,   0,  -2, -2 },
{ 0, -4,  -4,   0,  -4, -4 },
{ 5,  0,   0,   4,   0,   0 },
{ 0, -6,  -6,   0,  -6, -6 },
{ 5,  0,   0,   4,   0,   0 },
{ 5,  0,   0,   4,   0,   0 },
{ 0,  6,   0,   0,   11, 0 },
{ 0, -1,   7,   0,  -1, -1 },
{ 0, -3,  -3,   0,  -3, -3 },
{ 0, -5,  -5,   0,  -5, -5 }
};

int gotoTable[12][3] = {
/*       E   T   F  */
/* 0 */ { 1, 2, 3 },
/* 1 */ { 0, 0, 0 },
/* 2 */ { 0, 0, 0 },
/* 3 */ { 0, 0, 0 },
/* 4 */ { 8, 2, 3 },
/* 5 */ { 0, 0, 0 },
/* 6 */ { 0, 9, 3 },
/* 7 */ { 0, 0, 10 },
/* 8 */ { 0, 0, 0 },
/* 9 */ { 0, 0, 0 },
/*10 */ { 0, 0, 0 },
/*11 */ { 0, 0, 0 }
};

int getSymbolIndex(char c) {
    switch (c) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

int getGotoIndex(char nonterm) {
    switch (nonterm) {
        case 'E': return 0;
        case 'T': return 1;
        case 'F': return 2;
        default: return -1;
    }
}

int getTerminalIndex(char symbol) {
    switch (symbol) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1; 
    }
}


void push(int state, char symbol) {
    stack[top].state = state;
    stack[top].symbol = symbol;
    top++;
}

void pop(int n) {
    top -= n;
}

void printStack() {
    printf("Stack: ");
    for (int i = 0; i < top; i++) {
        printf("%c%d ", stack[i].symbol, stack[i].state);
    }
    printf("\n");
}

void parse() {
    push(0, '$'); 

    while (1) {
    int state = stack[top - 1].state;
    char symbol = input[ip];

    int col = getTerminalIndex(symbol);
    if (col == -1) {
        printf("Syntax error: invalid input symbol '%c'\n", symbol);
        break;
    }

    int action = actionTable[state][col];

    printf("Stack: ");
    for (int i = 0; i < top; i++) {
        printf("%c%d ", stack[i].symbol, stack[i].state);
    }
    printf("\nInput: %s\n", &input[ip]);

    if (action == 999) {
        printf("Action: Accept!\n");
        break;
    } else if (action > 0) {
        printf("Action: Shift and go to state %d\n", action);
        push(action, symbol);
        ip++;
    } else if (action < 0) {
        int prodIndex = -action - 1;
        const char* prod = productions[prodIndex];
        char lhs = prod[0];
        int rhsLen = strlen(prod) - 3;

        printf("Action: Reduce using %s\n", prod);

        pop(rhsLen);
        int newState = gotoTable[stack[top - 1].state][getGotoIndex(lhs)];
        push(newState, lhs);
    } else {
        printf("Syntax error!\n");
        break;
    }
}
}


int main() {
    printf("Enter the input string (use 'i' for id, end with $): ");
    scanf("%s", input);

    parse();

    return 0;
}
