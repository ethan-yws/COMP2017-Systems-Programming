#include <stdio.h>

int main(int argc, char** argv){
    char a[] = "hello";
    printf("%s\n", a);

    a[0] = '\0';
    printf("%s\n", a);
    return 0;
}