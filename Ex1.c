#define GLOBAL_INIT   42
#define GLOBAL_ZERO   0
#define STRING_LENGTH    16

#define GLOBAL_STRING "Hello World"
#define PMAP_PATH      "pmap"
#define PMAP_BIN      "pmap"
#define PMAP_OPTION   "-X"
#define DATA_TEXT "Data  :"
#define BSS_TEXT "BSS  :"
#define STR_TEXT "STR  :"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_init = GLOBAL_INIT;
int global_zero = GLOBAL_ZERO;
char *global_string = GLOBAL_STRING;

int main(void) {
    printf("%s %p\n",DATA_TEXT, (void *)&global_init);
    printf("%s %p\n",BSS_TEXT, (void *)&global_zero);
    printf("%s %p\n",STR_TEXT, (void *)global_string);

    char command[STRING_LENGTH];
    snprintf(command, sizeof(command), "%d", getpid());

    execlp(PMAP_PATH, PMAP_BIN, PMAP_OPTION, command, (char *)NULL);

    return 0;
}