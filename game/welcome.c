#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define pf printf

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m" 

pid_t music_pid;

void *play_music(void *arg) {
    music_pid = fork();
    if (music_pid == 0) {
        execlp("play", "play", "-q", "welcome-to-bali.mp3", (char *)NULL);
        perror("execlp failed");
        exit(1);
    }
    return NULL;
}

void stop_music() {
    if (music_pid > 0) {
        kill(music_pid, SIGTERM);
        wait(NULL);
    }
}

int main() {
    char c;
    pthread_t thread;

    if (pthread_create(&thread, NULL, play_music, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        system("clear");
        usleep(500000);
      
        pf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        pf(RED"             ██╗       ██╗███████╗██╗      █████╗  █████╗ ███╗   ███╗███████╗ \n"RESET);
        pf(GREEN"             ██║  ██╗  ██║██╔════╝██║     ██╔══██╗██╔══██╗████╗ ████║██╔════╝ \n"RESET);
        pf(YELLOW"             ╚██╗████╗██╔╝█████╗  ██║     ██║  ╚═╝██║  ██║██╔████╔██║█████╗   \n"RESET);
        pf(BLUE"              ████╔═████║ ██╔══╝  ██║     ██║  ██╗██║  ██║██║╚██╔╝██║██╔══╝   \n"RESET);
        pf(MAGENTA"              ╚██╔╝ ╚██╔╝ ███████╗███████╗╚█████╔╝╚█████╔╝██║ ╚═╝ ██║███████╗ \n"RESET);
        pf(CYAN"               ╚═╝   ╚═╝  ╚══════╝╚══════╝ ╚════╝  ╚════╝ ╚═╝     ╚═╝╚══════╝ \n"RESET);
        pf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      
        usleep(500000);
    }

    // Stop the music after the loop
    stop_music();

    printf("Press E to exit: ");
    scanf(" %c", &c);

    // Wait for the music thread to finish
    pthread_join(thread, NULL);
    return 0;
}
