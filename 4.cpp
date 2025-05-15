// Identidier = user defined varible name. Starts with A->Z || a->z || "_"

#include <stdio.h>
#include <ctype.h>

int main(){
    char a[10];
    int flag, i=1;
    printf("Enter the identifier: ");
    fgets(a, sizeof(a), stdin);

     for (int j = 0; a[j] != '\0'; j++) {
        if (a[j] == '\n') {
            a[j] = '\0';
            break;
        }
    }

    if (isalpha(a[0]) || a[0] == '_') {
        flag = 1;
    } else {
        printf("\nNot a valid identifier");
        return 0;
    }

    while(a[i]!='\0'){
        if(!isalnum(a[i]) && a[i] != '_'){
            flag = 0;
            break;
        }
        i++;
    }
    if(flag==1) printf("\n Valid Identifier");
    else printf("\n Not Valid Identifier\n");
}