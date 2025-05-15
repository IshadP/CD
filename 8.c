// #include <stdio.h>
// #include <string.h>

// char input[100];
// int i = 0;

// int E();
// int EPrime();
// int T();
// int TPrime();
// int F();

// int main() {
//     printf("Recursive Descent Parsing for the following grammar:\n");
//     printf("E -> T E'\nE' -> + T E' | ε\nT -> F T'\nT' -> * F T' | ε\nF -> (E) | id\n");

//     printf("Enter the string to be checked: ");
//     fgets(input, sizeof(input), stdin);
//     input[strcspn(input, "\n")] = '\0'; 
//     i = 0;

//     if (E() && (input[i] == '\0')) {
//         printf("String accepted\n");
//     } else {
//         printf("String rejected\n");
//     }

//     return 0;
// }

// int E() {
//     if (T()) {
//         return EPrime();
//     }
//     return 0;
// }

// int EPrime() {
//     if (input[i] == '+') {
//         i++;
//         if (T()) {
//             return EPrime();
//         }
//         return 0;
//     }
//     return 1;  
// }

// int T() {
//     if (F()) {
//         return TPrime();
//     }
//     return 0;
// }

// int TPrime() {
//     if (input[i] == '*') {  
//         i++;
//         if (F()) {
//             return TPrime();
//         }
//         return 0;
//     }
//     return 1;  
// }

// int F() {
//     if (input[i] == '(') {
//         i++;
//         if (E()) {
//             if (input[i] == ')') {
//                 i++;
//                 return 1;
//             }
//             return 0;
//         }
//         return 0;
//     } else if ((input[i] >= 'a' && input[i] <= 'z') || 
//                (input[i] >= 'A' && input[i] <= 'Z')) {
//         i++;
//         return 1;
//     }
//     return 0;
// }


// 8a

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char input[MAX];
int ip = 0;

char stack[MAX];
int top = -1;

void push(char symbol) {
    stack[++top] = symbol;
}

char pop() {
    return (top >= 0) ? stack[top--] : '\0';
}

char peek() {
    return (top >= 0) ? stack[top] : '\0';
}

char nextToken() {
    while (isspace(input[ip])) ip++;
    return input[ip];
}

int isId(char ch) {
    return isalpha(ch);
}

void parse() {
    push('$');
    push('E');

    char X, a;

    while ((X = pop()) != '$') {
        a = nextToken();

        if (X == a) {
            ip++;
        } else {
            switch (X) {
                case 'E':
                    push('Q');
                    push('T');
                    break;
                case 'Q':
                    if (a == '+') {
                        push('Q');
                        push('T');
                        push('+');
                    }
                    break;
                case 'T':
                    push('R');
                    push('F');
                    break;
                case 'R':
                    if (a == '*') {
                        push('R');
                        push('F');
                        push('*');
                    }
                    break;
                case 'F':
                    if (a == '(') {
                        push(')');
                        push('E');
                        push('(');
                    } else if (isId(a)) {
                        push('i');
                    } else {
                        printf("Rejected: invalid token in F\n");
                        return;
                    }
                    break;
                case 'i':
                    if (isId(a)) {
                        ip++;
                    } else {
                        printf("Rejected: expected identifier\n");
                        return;
                    }
                    break;
                default:
                    printf("Rejected: unknown non-terminal %c\n", X);
                    return;
            }
        }
    }

    if (input[ip] == '\0') {
        printf("Accepted\n");
    } else {
        printf("Rejected: extra input remaining\n");
    }
}

int main() {
    printf("Enter expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    parse();
}