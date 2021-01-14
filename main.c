#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int  count_ttys();
void start_gettys(int count);
void exec_getty(int id);

int main(int argc, char* argv[]) {
    printf("init: aaa\n");

    if (!fork()) {
        char* argv[] = {
            "utest",
            NULL,
        };

        printf("asdasda\n");

        execve("/sys/utest", argv, NULL);
    }

    start_gettys(count_ttys());

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

int count_ttys() {
    int count = 0;

    for (int i = 0; i < 32; i++) {
        char buffer[32];

        sprintf(buffer, "/dev/tty%i", i);
        if (access(buffer, F_OK) == -1)
            break;

        count++;
    }

    return count;
}

void start_gettys(int count) {
    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (pid)
            continue;

        exec_getty(i);
    }
}

void exec_getty(int id) {
    char buffer[64];
    sprintf(buffer, "/dev/tty%i", id);

    char* argv[] = {
        "getty",
        buffer,
        NULL,
    };

    execve("/bin/getty", argv, NULL);
}