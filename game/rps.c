#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main() {
	int op,cp,user=0,computer=0;
	char ch;
	srand(time(0));
	while (1)
	{
	    system("clear");
		printf("\n\tUser = %d\tComputer = %d\n\n",user,computer);
		printf("\t1)ROCK\n\t2)PAPER\n\t3)SCISSORS\n\tENTER THE OPTION : ");
		scanf("%d",&op);
		cp=rand()%100;
		cp=cp<=33?1:(cp>66?3:2);
		if (cp==op){
		    printf("\n\t\t\tDrawn the slot\n");
		    goto exit;
		} 
		else
		{
			usleep(100000);
    		
			if (((cp==1)&&(op==2))||((cp==2)&&(op==3))||((cp==3)&&(op==1)))
			{
			    user++;
			    if(user==3) goto exit;
				printf("\n\t\t\tUser is WON the slot\n");
			} else {
			    computer++;
			    if(user==3) goto exit;
				printf("\n\t\t\tComputer is WON the slot\n");
			}
		}
		exit:
		if(user==3) {
    			printf("\n\t\t\t\tUser = %d\n\t\t\tUser is WON the match\n",user);
    			exit(0);
    		} else if(computer==3) {
    			printf("\n\t\t\t\tComputer = %d\n\t\t\tComputer is WON the match\n");
    			exit(0);
    		}
		printf("\n\tPress any key to continue");
		scanf(" %c",&ch);
	}

}