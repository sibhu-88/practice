//    1. Write a program to execute ls , pwd & cal sequentially
//	  a) Using system( )
//	  b) Using exec( )
//		Hint : use fork().

#include<stdio.h>
#include<unistd.h>

int main(){
	char *str[3]={"/bin/ls","/bin/pwd","/usr/bin/cal"};
	for(int i=0;i<3;i++){
		if(fork()==0){
			execl(str[i],str[i],NULL);
			sleep(1);
			perror("execlp");
			return 1;
		}
	}
}
