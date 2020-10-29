#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < 5; i++)
        syscall(251 + i, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE);

    // sleep(3);
    fwrite("test\n", 5, 5, stdout);

    return 0;
}