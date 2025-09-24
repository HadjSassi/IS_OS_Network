#define GLOBAL_INIT   42
#define GLOBAL_ZERO   0
#define STRING_LENGTH    16
#define STACK_INIT     123
#define HEAP_INIT      999

#define GLOBAL_STRING "Hello World"
#define PMAP_PATH      "pmap"
#define PMAP_BIN      "pmap"
#define PMAP_OPTION   "-X"
#define DATA_TEXT "Data  :"
#define BSS_TEXT "BSS  :"
#define STR_TEXT "STR  :"
#define HEAP_TEXT  "Heap    :"
#define STACK_TEXT  "Stack   :"
#define MAIN_TEXT   "Main func  :"
#define LIBC_TEXT   "LibC func  :"
#define MMAP_TEXT   "Mmap       :"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int global_init = GLOBAL_INIT;
int global_zero = GLOBAL_ZERO;
char *global_string = GLOBAL_STRING;

int main(void) {
    int stack_var = STACK_INIT;

    int *heap_var = malloc(sizeof(int));
    if (!heap_var) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    *heap_var = HEAP_INIT;

    // Mmap allocation
    void *mmap_var = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mmap_var == MAP_FAILED) {
        perror("mmap failed");
        free(heap_var);
        exit(EXIT_FAILURE);
    }

    printf("%s %p\n",DATA_TEXT, (void *)&global_init);
    printf("%s %p\n",BSS_TEXT, (void *)&global_zero);
    printf("%s %p\n",STR_TEXT, (void *)global_string);
    printf("%s %p\n", HEAP_TEXT, (void *)heap_var);
    printf("%s %p\n", STACK_TEXT, (void *)&stack_var);
    printf("%s %p\n", MAIN_TEXT, (void *)main);
    printf("%s %p\n", LIBC_TEXT, (void *)printf);
    printf("%s %p\n", MMAP_TEXT, mmap_var);

    char command[STRING_LENGTH];
    snprintf(command, sizeof(command), "%d", getpid());

    execlp(PMAP_PATH, PMAP_BIN, PMAP_OPTION, command, (char *)NULL);

    perror("execlp failed");
    free(heap_var);
    munmap(mmap_var, 4096);

    return 0;
}