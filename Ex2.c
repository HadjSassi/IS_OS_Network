#define OPEN_FLAG 0644
#define SUCCESS_EXIT 0
#define FAILURE_EXIT (-1)
#define FAILURE_FLAG 0
#define OFFSET  0
#define FILE_NAME "test.txt"
#define TEXT_CONTENT "HELLO WORLD\nThis is the repository of HADJ SASSI Mahdi and BAATOUT Chahrazed"
#define OPENING_ERROR "open"
#define WRITING_ERROR "write"
#define FILE_STATUS_ERROR "fstat"
#define MMAP_ERROR "mmap"
#define TEXT_BEFORE_INSERTION "Before Insertion : "
#define TEXT_AFTER_INSERTION "After Insertion : "
#define TEXT_FILE_SIZE "The size of the file is : "
#define FILE_UNIT "bytes"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


void write_file(const char *filename, const char *content) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_FLAG);
    if (fd < FAILURE_FLAG) {
        perror(OPENING_ERROR);
        exit(FAILURE_EXIT);
    }
    ssize_t written = write(fd, content, strlen(content));
    if (written < FAILURE_FLAG) {
        perror(WRITING_ERROR);
        close(fd);
        exit(FAILURE_EXIT);
    }
    close(fd);
}

int open_file_rw(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < FAILURE_FLAG) {
        perror(OPENING_ERROR);
        exit(FAILURE_EXIT);
    }
    return fd;
}

void get_file_size(int fd, size_t *size) {
    struct stat st;
    if (fstat(fd, &st) < FAILURE_FLAG) {
        perror(FILE_STATUS_ERROR);
        exit(FAILURE_EXIT);
    }
    *size = st.st_size;
}

char* map_file(int fd, size_t size) {
    char *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, OFFSET);
    if (data == MAP_FAILED) {
        perror(MMAP_ERROR);
        exit(FAILURE_EXIT);
    }
    return data;
}

void reverse_content(char *data, size_t size) {
    for (size_t i = OFFSET; i < size / 2; i++) {
        char tmp = data[i];
        data[i] = data[size - 1 - i];
        data[size - 1 - i] = tmp;
    }
}

int main() {
    const char *filename = FILE_NAME;
    const char *new_content = TEXT_CONTENT;
    size_t size;

    write_file(filename, new_content);

    int fd = open_file_rw(filename);

    get_file_size(fd, &size);

    printf("%s %zu %s\n", TEXT_FILE_SIZE, size, FILE_UNIT);

    char *data = map_file(fd, size);

    printf("\n\n%s\n\n%.*s\n\n", TEXT_BEFORE_INSERTION, (int)size, data);

    reverse_content(data, size);

    printf("\n\n%s\n\n%.*s\n\n", TEXT_AFTER_INSERTION, (int)size, data);

    munmap(data, size);
    close(fd);
    return SUCCESS_EXIT;
}