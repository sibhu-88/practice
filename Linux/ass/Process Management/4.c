#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // For malloc and free

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("USAGE : ./a.out COMMANDS\n");
        return 0;
    }

    int i, j, k = 0, rtn, count = 0;

    // Count the number of commas in the string to determine the number of commands
    for (i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] == ',') ++count;
    }
    count += 1; // The number of commands is the number of commas + 1

    printf("COMMANDS count = %d\n", count);

    // Allocate memory for each command
    char **str = (char **)malloc(count * sizeof(char *));
    if (!str) {
        perror("malloc");
        return 1;
    }

    // Allocate memory for each command string
    for (i = 0; i < count; i++) {
        str[i] = (char *)malloc(20 * sizeof(char)); // Assuming each command is <= 20 characters
        if (!str[i]) {
            perror("malloc");
            return 1;
        }
    }

    // Split the input string into individual commands based on commas
    k = 0;
    j = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] != ',') {
            str[k][j++] = argv[1][i];
        } else {
            str[k][j] = '\0'; // Null-terminate the current command
            k++;              // Move to the next command
            j = 0;            // Reset index for the next command
        }
    }
    str[k][j] = '\0'; // Null-terminate the last command

    // Now execute each command
    for (i = 0; i < count; i++) {
        printf("\nExecuting command: %s\n", str[i]);

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // In the child process, execute the command
            execlp(str[i], str[i], NULL);
            perror("execlp"); // If execlp fails, print an error
            exit(1);          // Exit the child process if execlp fails
        } else {
            // In the parent process, wait for the child to finish
            wait(NULL);
        }
        printf("---------------------------------------------------------\n");
    }

    // Free the dynamically allocated memory
    for (i = 0; i < count; i++) {
        free(str[i]);
    }
    free(str);

    return 0;
}

