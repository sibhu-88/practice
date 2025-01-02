//Modify the above program .So that no two jobs have the common parent.
//{each job have different parent).
//	 x------bash
//	x+1 --- x
//	x+2----x+1
//	x+3---x+2


#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int main(){
	if(fork()==0){
		printf("Parent==> %d child ==>%d\n",getppid(),getpid());
		if(fork()==0){
			printf("Parent==> %d child ==>%d\n",getppid(),getpid());
			if(fork()==0){
				printf("Parent==> %d child ==>%d\n",getppid(),getpid());
			}
		}
	}

}


