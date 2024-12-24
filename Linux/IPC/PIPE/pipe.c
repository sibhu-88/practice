#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


int main(){
	int fd[2],ret,ch=0,par=0;
	char a[20];

	ret = pipe(fd);
	if(ret==-1){
		perror("pipe"); return 0;
	}

	while(1){
	  if(fork()==0){
		bzero(a,20);
		printf("Enter the string : ");
		scanf(" %[^\n]",a);
		printf("Child = %d\tPID = %d\n",ch++,getpid());
		write(fd[1],a,strlen(a)+1);
		return 0;
	//	sleep(1);
	  }else{
		bzero(a,20);
		printf("Parent = %d\tPID = %d\n",par++,getpid());
		read(fd[0],a,sizeof(a));
		printf("In parent : %s\n",a);
		wait(NULL);
	  }
	}

}
