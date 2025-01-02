//    5. Write a program to execute the no of commands from command line
//       a) using system( )
//        b) using exec()
//              Note : no of new process create must be euql to no of cmd given at command line)
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("USAGE : ./a.out COMMANDS\n");
        return 0;
    }

    int i, j, k = 0, rtn, count = 0;

    for (i = 1; i <= argc; i++) {
	   if(fork()==0){
           	system(argv[i]); 
		printf("--------------------------------------------------------------------\n");
	      execlp(argv[i], argv[i], NULL);
            	perror("execlp"); 
	    //	exit(0);
	    }else{
		printf("--------------------------------------------------------------------\n");
		wait(0);
	   }
    }

    return 0;
}

