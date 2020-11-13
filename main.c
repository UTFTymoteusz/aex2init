#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
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