#include <stdio.h>
#include <ctype.h>
#include <string.h>

void keywords(char str[10]){
    if(strcmp("for",str)||strcmp("while",str)||strcmp("do",str)||strcmp("int",str)||strcmp("float",str)||strcmp("char",str)||strcmp("double",str)||strcmp("static",str)||strcmp("switch",str)||strcmp("case",str))
    printf("%s is a keyword\n",str);
    else
    printf("%s is and identifier", str)
}

void main(){
    FILE *f1, *f2, *f3;
    char c, str[10], st1[10];
    printf("\nEnter the c program")
    f1 = fopen("input", "w");
    while((c=getchar())!=EOF){
        putc(c.f1);
    }
    fclose(f1);
    f1 = fopen("input", "r");
    f2 = fopen("identifier", "w");
    f3 = fopen("specialchar", "w");
}