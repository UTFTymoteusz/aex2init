#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void _set_errno(int);

int main(int argc, char* argv[]) {
    syscall(126);
    printf("errno: %i\n", errno);

    fwrite("test\n", 5, 1, stdout);

    FILE* file = fopen("/sys/test.txt", "r");

    char buffer[72];
    fread(buffer, 64, 1, file);

    buffer[64] = '\0';
    fwrite(buffer, 64, 1, stdout);

    putc('\n', stdout);
    printf("asdada %s\n", "it works");

    return 0;
}