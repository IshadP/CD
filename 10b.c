#include <stdio.h>
#include <string.h>

#define MAX 100

char precedence[7][7] = {
    //   +    *    i    (    )    $    
    /*+*/ {'>', '<', '<', '<', '>', '>'},
    /***/ {'>', '>', '<', '<', '>', '>'},
    /*i*/ {'>', '>', 'e', 'e', '>', '>'},
    /*(*/ {'<', '<', '<', '<', '=', 'e'},
    /*)*/ {'>', '>', 'e', 'e', '>', '>'},
    /*$*/ {'<', '<', '<', '<', 'e', '='},
};

int getIndex(char c) {
    switch(c) {
        case '+': return 0;
        case '*': return 1;
        case 'i': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return (top >= 0) ? stack[top--] : '\0';
}

char topTerminal() {
    for (int i = top; i >= 0; i--) {
        if (stack[i] != 'E') return stack[i];
    }
    return '\0';
}

void printStackInput(const char *input, int ip) {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\tInput: %s\n", &input[ip]);
}

int main() {
    char input[MAX];
    printf("Enter the input string (use 'i' for id, end with $): ");
    scanf("%s", input);

    push('$');
    int ip = 0;

    printf("\nParsing Steps:\n");

    while (1) {
        printStackInput(input, ip);
        char a = topTerminal();
        char b = input[ip];

        if (a == '$' && b == '$') {
            if (stack[1] == 'E' && top == 1) {
                printf("Input accepted!\n");
            } else {
                printf("Syntax error: incomplete reduction.\n");
            }
            break;
        }

        int row = getIndex(a);
        int col = getIndex(b);

        if (row == -1 || col == -1) {
            printf("Syntax error: invalid symbol '%c'\n", b);
            break;
        }

        char relation = precedence[row][col];

        if (relation == '<' || relation == '=') {
            printf("Action: Shift '%c'\n", b);
            push(b);
            ip++;
        } else if (relation == '>') {
            printf("Action: Reduce\n");

            if (stack[top] == 'i') {
                pop();
                push('E');
            } else if (stack[top] == ')') {
                if (stack[top - 2] == '(' && stack[top - 1] == 'E') {
                    pop(); pop(); pop();
                    push('E');
                } else {
                    printf("Syntax error: invalid grouping\n");
                    break;
                }
            } else if (stack[top - 2] == 'E' &&
                      (stack[top - 1] == '+' || stack[top - 1] == '*') &&
                       stack[top] == 'E') {
                pop(); pop(); pop();
                push('E');
            } else {
                printf("Syntax error: unable to reduce\n");
                break;
            }
        } else {
            printf("Syntax error: invalid precedence\n");
            break;
        }
    }

    return 0;
}
