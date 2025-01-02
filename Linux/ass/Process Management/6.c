//    6. Write a program to creat  3 new  jobs , in such a manner that all the 3 new jobs should have common parent.
// x------bash
// x+1 --- x
// x+2----x
// x+3---x

#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int main(){
	if(fork()==0){
		printf("Parent==> %d child ==>%d\n",getppid(),getpid());
	}else{
		if(fork()==0){
			printf("Parent==> %d child ==>%d\n",getppid(),getpid());
		}else{
			if(fork()==0){
				printf("Parent==> %d child ==>%d\n",getppid(),getpid());
			}
		}
	}

}
