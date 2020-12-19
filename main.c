#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void _set_errno(int);
void test();
int  count_ttys();

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (!pid) {
        char* argv[] = {
            "utest.elf",
            NULL,
        };

        execve("/sys/utest.elf", argv, NULL);
    }

    while (true) {
        int   status;
        pid_t pid = wait(&status);

        if (pid == -1) {
            if (errno == ECHILD) {
                printf("init: No children left, exiting...\n", pid, status);
                break;
            }
            else
                perror("init: waitpid: ");

            sleep(2);
            continue;
        }

        printf("init: pid%i exited with a code %i\n", pid, status);
    }

    return 0;
}