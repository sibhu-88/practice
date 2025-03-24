#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


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
        execlp("play", "play", "-q", "Dice.mp3", (char *)NULL);
        
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
void dicess_1(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_2(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0           |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|           0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_3(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0           |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|           0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_4(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_5(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_6(void){
	printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}


int main(){
	int i,j,ran;
	char op;
	void (*fdicess[])(void) = {dicess_1, dicess_2, dicess_3, dicess_4, dicess_5, dicess_6};

	pthread_t thread;

	do{
		printf("Type S to start Dicess : ");
		scanf(" %c",&op);
		op=tolower(op);
		if(op!='s') break;

		if (pthread_create(&thread, NULL, play_music, NULL) != 0) {
		        perror("Failed to create thread");
		        return 1;
    		}

		srand(time(0));
		ran=rand() % 6;
		for ( i = 0; i < 9; i++) {
			for(j=0;j<6;j++){
				system("clear");
        			fdicess[j]();
				usleep(50000);
			}
		}
		
		system("clear");
		fdicess[ran]();
		printf("You got %d \n",ran+1);
		stop_music();
		printf("Do you want to Dice again (Y/N): ");
                scanf(" %c",&op);
                op=tolower(op);
	}while(op=='y');
}

