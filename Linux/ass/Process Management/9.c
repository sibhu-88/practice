//9 .In the above program the o/p sequence must be date->pwd->cal->ls
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Execute ls command
    if ((pid = fork()) == 0) {
        execlp("date", "date", NULL);
        perror("execlp ls failed"); // Print error if execlp fails
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    wait(NULL); // Wait for the ls command to finish

    // Execute pwd command
    if ((pid = fork()) == 0) {
        execlp("pwd", "pwd", NULL);
        perror("execlp pwd failed");
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    wait(NULL); // Wait for the pwd command to finish

    // Execute cal command
    if ((pid = fork()) == 0) {
        execlp("cal", "cal", NULL);
        perror("execlp cal failed");
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    wait(NULL); // Wait for the cal command to finish

    // Execute date command
    if ((pid = fork()) == 0) {
        execlp("ls", "ls", NULL);
        perror("execlp date failed");
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    wait(NULL); // Wait for the date command to finish

    return 0;
}
