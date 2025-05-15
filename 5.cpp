#include <stdio.h>

int main(){
    char s[5];
    printf("\nEnter the operator: ");
    fgets(s, sizeof(s), stdin);
    switch(s[0]){
        case '>':
            if(s[1] == '=') printf("Greater than equal to\n");
            else if(s[1] == '>') printf("Bit shift right\n");
            else printf("Greater than\n");
            break;
        case '<':
            if(s[1] == '=') printf("Greater than equal to\n");
            else if(s[1] == '<') printf("Bit shift left\n");
            else printf("Greater than\n");
            break;
        case '=':
            if(s[1] == '=') printf("Equal to\n");
            else printf("Assignment\n");
            break;
        case '!':
            if(s[1] == '=') printf("Not equal to\n");
            else printf("Bit Not\n");
            break;
        default:
            break;

// Similarily do cases for +, -, \, /, |, %, >>, <<, !==, &, ++, --, ^, *, 
    }
}