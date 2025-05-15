// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main(){
//     char s[20], c;
//     int state = 0, i = 0;
//     printf("Enter the string: ");
//     fgets(s, sizeof(s), stdin); 

//     while(s[i]!='\0'){
//         switch (state)
//         {
//         case 0:
//             c=s[i++];
//             if(c=='a') state=1;
//             if(c=='b') state=2;
//             else state=3;
//             break;

//         case 1:
//             c = s[i++];
//             if(c=='a') state=1;
//             if(c=='b') state=2;
//             break;
//         case 2:
//             c=s[i++];
//             if(c=='b') state=3;
//             else state=3;
//             break;
//         case 3:
//             printf("String recognised");
//             break;
        
//         default:
//             break;
//         }        
//     }
// return 0;
// }

#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    int state = 0, i = 0;
    char c;

    printf("Enter the string: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    while (s[i] != '\0') {
        c = s[i++];

        switch(state) {
            case 0:
                if (c == 'a') {
                    state = 0;  
                } else if (c == 'b') {
                    state = 1; 
                } else {
                    state = 2;
                }
                break;

            case 1:
                if (c == 'b') {
                    state = 1;
                } else {
                    state = 2; 
                }
                break;

            case 2:
                break;
        }
    }

    if (state == 1 || state == 0) {
        printf("String recognised\n");
    } else {
        printf("String not recognised\n");
    }

    return 0;
}
