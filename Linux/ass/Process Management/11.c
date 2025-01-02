/*Modify the above program so that parent will wait uptp child -2 exit.sp after child-2 parent will laso exit and another child become may be in Zombie or Orphan.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	int delay,stat,i;
	pid_t pid[3];

	srand(time(0));
	for(i=0;i<3;i++){
		delay=rand()%10+1;
		if((pid[i]=fork())==0){
			printf("Child %d (PID: %d) sleeping for %d seconds.\n", i + 1, getpid(), delay);
			sleep(delay);
			printf("Child %d (PID: %d) exiting after %d seconds.\n", i + 1, getpid(), delay);
			exit(i + 1);
		}

		delay=rand()%10+1;
	}

	waitpid(pid[1],&stat,0);
	printf("Child 2 exited with status: %d\n", WEXITSTATUS(stat));
	printf("Parent (PID: %d) exiting after child 2.\n", getpid());
	exit(0);

}
