/*Write a program to i/p 2 small(1 to 50) integers from command line and add two interger in child process and print the sum in parent process.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("USAGE : ./a.out oprent1 oprent2\n");
        return 0;
    }

	int num1 = atoi(argv[1]);
    	int num2 = atoi(argv[2]);


    if (num1 < 1 || num1 > 50 || num2 < 1 || num2 > 50) {
        fprintf(stderr, "Both integers must be between 1 and 50.\n");
        return 1;

    }

    int sum = 0;
	   if(fork()==0){
           	sum = num1 + num2;
		exit(sum);
	   }else{
		wait(&sum);
		printf("sum = %d\n",WEXITSTATUS(sum));
	   }

    return 0;
}
