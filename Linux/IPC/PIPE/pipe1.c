#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {
    int fd[2], ret;
    char a[20];
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        return 1;
    }

    while (1) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            bzero(a, 20);
            printf("Child PID = %d \nEnter the string: ", getpid());
            fgets(a, sizeof(a), stdin);

            write(fd[1], a, strlen(a) + 1);
            return 0;
        } else { // Parent process
            bzero(a, 20);
            read(fd[0], a, sizeof(a));
            printf("Parent PID = %d: \nIn parent: %s\n", getpid(), a);
            wait(NULL); // Wait for the child to finish
        }
    }

    return 0;
}
