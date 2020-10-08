#include <unistd.h>

int main(int argc, char* argv[]) {
    syscall(6);
    return 0;
}