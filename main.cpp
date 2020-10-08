#include <unistd.h>

int main(int argc, char* argv[]) {
    syscall(0);
    return 0;
}