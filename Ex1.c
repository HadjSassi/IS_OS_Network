#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_init = 42;

int global_zero = 0;

char *str = "Hello World";

int main(void) {


    printf("Data : %p\n", (void*)&global_init);
    printf("BSS  : %p\n", (void*)&global_zero);
    printf("Str  : %p\n", (void*)str);

    printf("\n Hello memory  :\n");
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "pmap -X %d", getpid());
    system(cmd);

    return 0;
}