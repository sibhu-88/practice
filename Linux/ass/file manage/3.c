//WAP to compare the links of two files ,input from command line?
#include<stdio.h>
#include <stdlib.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		printf("./a.out file1 file2\n");
		return 0;
	}

	struct stat st1;
	int rd1;
	 rd1= lstat(argv[1],&st1);
	if(rd1==-1){
		perror("lstat");
               exit(EXIT_FAILURE);
	}
	switch (st1.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;//macro
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
        }
	//if(S_ISREG(st1.st_mode)){} pre define fun

}
