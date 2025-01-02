// 8.In the above given prog execute ls, pwd ,cal ,date command by x,x+1,x+2,x+3 respectively.

#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int main(){
	if(fork()==0){
		execlp("ls","ls",NULL);
		printf("-----------------------------------------------------------------------------------");
		exit(0);
	}else{
		if(fork()==0){
			execlp("pwd","pwd",NULL);
			printf("-----------------------------------------------------------------------------------");
			exit(0);
		}else{
			if(fork()==0){
				execlp("cal","cal",NULL);
				printf("-----------------------------------------------------------------------------------");
				exit(0);
			}else{
				if(fork()==0){
					execlp("date","date",NULL);
					printf("-----------------------------------------------------------------------------------");
					exit(0);
				}
			}
		}
	}

}
