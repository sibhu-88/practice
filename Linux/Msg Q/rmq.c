#include<stdio.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
struct mbuf {
	long mtype;
	char mtext[50];
};


int main(int argc, char *argv[])
{
	if(argc!=2){
		printf("USAGE : ./a.out type\n"); return 0;
	}
	
	int id,ret;
	struct mbuf msg;

	id=msgget(5,IPC_CREAT|0644);
	if(id<0){
		perror("msgget"); return 0;
	}

	ret=msgrcv(id,&msg,sizeof(msg.mtext),atoi(argv[1]),IPC_NOWAIT);

	if(ret<0){
		perror("msgrcv"); return 0;
	}

	printf("Message recive successfully\n ===>%ld ==>  %s\n",msg.mtype,msg.mtext);

}
