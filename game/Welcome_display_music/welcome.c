#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> // For open()

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
   int devNull = open("/dev/null", O_WRONLY);
    if (devNull < 0) {
        perror("open");
        return NULL;
    }


    if ( (music_pid = fork()) < 0) {
        perror("fork");
        return NULL;
    }

    if (music_pid == 0) {
        dup2(devNull, STDOUT_FILENO);
        dup2(devNull, STDERR_FILENO);
        close(devNull); 
        execlp("play", "play", "-q", "welcome-to-bali.mp3", (char *)NULL);
        
        perror("execl failed");
        exit(1);
    }
   close(devNull);
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
        pf(RED"\t\t\t\t  ██╗       ██╗███████╗██╗      █████╗  █████╗ ███╗   ███╗███████╗ \n"RESET);
        pf(GREEN"\t\t\t\t  ██║  ██╗  ██║██╔════╝██║     ██╔══██╗██╔══██╗████╗ ████║██╔════╝ \n"RESET);
        pf(YELLOW"\t\t\t\t  ╚██╗████╗██╔╝█████╗  ██║     ██║  ╚═╝██║  ██║██╔████╔██║█████╗   \n"RESET);
        pf(BLUE"\t\t\t\t   ████╔═████║ ██╔══╝  ██║     ██║  ██╗██║  ██║██║╚██╔╝██║██╔══╝   \n"RESET);
        pf(MAGENTA"\t\t\t\t   ╚██╔╝ ╚██╔╝ ███████╗███████╗╚█████╔╝╚█████╔╝██║ ╚═╝ ██║███████╗ \n"RESET);
        pf(CYAN"\t\t\t\t    ╚═╝   ╚═╝  ╚══════╝╚══════╝ ╚════╝  ╚════╝ ╚═╝     ╚═╝╚══════╝ \n"RESET);
        pf("\n\n\n\n\n \n\n\n\n\n\n\n\n\n\n\n\n");
      
        usleep(500000);
    }

    stop_music();

    printf("Press E to exit: ");
    scanf(" %c", &c);

    pthread_join(thread, NULL);
    return 0;
}
