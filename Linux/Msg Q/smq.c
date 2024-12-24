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
	if(argc!=3){
		printf("USAGE : ./a.out type msg\n"); return 0;
	}
	
	int id,ret;
	struct mbuf msg;

	id=msgget(5,IPC_CREAT|0644);
	if(id<0){
		perror("msgget"); return 0;
	}

	msg.mtype=atoi(argv[1]);
	
	strcpy(msg.mtext,argv[2]);

	ret=msgsnd(id,&msg,strlen(msg.mtext)+1,0);

	if(ret<0){
		perror("msgsnd"); return 0;
	}

	printf("Message sent successfully\n");

}
