#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    char* fname = argv[1];

    FILE* f;
    f = fopen(fname, "rb");

    if(!f){
        perror("failed\n");
        return 1;
    }

    char * buffer;
    fseek(f, 0, SEEK_END);
    unsigned long len = ftell(f);
    fread(&buffer, sizeof(char), len, f);

    printf("%lu\n", len);

    rewind(f);
    printf("%s\n", buffer);

    return 0;
}