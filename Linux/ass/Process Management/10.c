//    11. Write a program to create a three child process from the common parent use random delay between 1to 10 sec in each child. Use the exit value in such a manner so that parent should know the sequence of the child exits.
     /* Hint : while(wait(&status)!=-1)
		{
;
		}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	int delay,stat,i;

	srand(time(0));
	for(i=0;i<3;i++){
		delay=rand()%10+1;
		if(fork()==0){
			printf("Child %d (PID: %d) sleeping for %d seconds.\n", i + 1, getpid(), delay);
			sleep(delay);
			printf("Child %d (PID: %d) exiting after %d seconds.\n", i + 1, getpid(), delay);
			exit(i + 1);
		}

		delay=rand()%10+1;
	}

	while(wait(&stat)!=-1){
		printf("Child exited with status: %d\n", WEXITSTATUS(stat));
	}


}

