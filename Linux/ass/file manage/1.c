//WAP to find the size of file without opening the file?
#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("./a.out file\n");
		return 0;
	}

	struct stat st;
	int rd = stat(argv[1],&st);
	if(rd==-1){
		perror("stat");
               exit(EXIT_FAILURE);
	}
	printf("Size of File  = %lld\n",st.st_size);

}
