// 2. Write a program to execute a command with its arguments given at command line.
//	i/p :  ./a.out  ls –l
//	   ./a.out cal 2011.

#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[]){
			if(0>execlp(argv[1],argv[1],argv[2],NULL)){
			perror("execlp"); return 0;
			}
}
