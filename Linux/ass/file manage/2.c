//WAP to compare the size of two files ,input from command line
#include<stdio.h>
#include <stdlib.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	if(argc!=3){
		printf("./a.out file1 file2\n");
		return 0;
	}

	struct stat st1,st2;
	int rd1,rd2;
	 rd1= stat(argv[1],&st1);
	 rd2= stat(argv[2],&st2);
	if(rd1==-1||rd2==-1){
		perror("stat");
               exit(EXIT_FAILURE);
	}
	if(st1.st_size==st2.st_size)
		printf("Both file size are same\n");
	else
		printf("File1 = %ld File2 = %ld\n",st1.st_size,st2.st_size);

}
