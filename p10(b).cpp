#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input;
int pos = 0;

// Forward declarations
int E();
int Eprime(int inherited);
int T();
int Tprime(int inherited);
int F();

char lookahead() {
    return input[pos];
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        printf("Syntax Error: expected '%c' but found '%c'\n", expected, input[pos]);
        exit(1);
    }
}

// F -> number (multi-digit)
int F() {
    if (!isdigit(lookahead())) {
        printf("Syntax Error: expected digit but found '%c'\n", lookahead());
        exit(1);
    }

    int num = 0;
    while (isdigit(lookahead())) {
        num = num * 10 + (input[pos] - '0');
        pos++;
    }
    return num;
}

// T' -> * F T' | ε
int Tprime(int inherited) {
    if (lookahead() == '*') {
        match('*');
        int fval = F();
        return Tprime(inherited * fval);
    }
    return inherited; // ε
}

// T -> F T'
int T() {
    int fval = F();
    return Tprime(fval);
}

// E' -> + T E' | ε
int Eprime(int inherited) {
    if (lookahead() == '+') {
        match('+');
        int tval = T();
        return Eprime(inherited + tval);
    }
    return inherited; // ε
}

// E -> T E'
int E() {
    int tval = T();
    return Eprime(tval);
}

int main() {
    char expr[100];
    printf("Enter an expression (digits, +, *): ");
    scanf("%s", expr);

    input = expr;
    int result = E();

    if (input[pos] != '\0') {
        printf("Syntax Error: unexpected character '%c'\n", input[pos]);
        return 1;
    }

    printf("Result = %d\n", result);
    return 0;
}
