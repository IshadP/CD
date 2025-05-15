#include <stdio.h>

int main() {
    char c[100];
    printf("Enter comment: ");
    fgets(c, sizeof(c), stdin);  // Use fgets instead of gets

    if(c[0] == '/') {
        if(c[1] == '/' || c[1] == '*') {
            printf("This is a comment");
        } else {
            printf("This is not a comment");
        }
    } else {
        printf("This is not a comment");
    }

    return 0;
}
