#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<termios.h>

int open_port(void)
{
	printf("port function...\n");
	int fd;
	fd=open("/dev/ttyS0",O_RDWR|O_NOCTTY|O_NDELAY);
 	if(fd==-1)
	{
		perror("open_port:Unable to open /dev/ttyS0 - ");
	}
	else
	fcntl(fd,F_SETFL,0);
	printf("port function executed successfully....\n");
	return (fd);
}

int init_serialcom(int fd)
{
	printf("configuration...\n");
	struct termios options;
	tcgetattr(fd,&options);
	cfsetispeed(&options,B9600);
	
	cfsetospeed(&options,B9600);
	options.c_cflag |= (CLOCAL|CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
 	options.c_cflag |= CS8;
	tcsetattr(fd,TCSANOW,&options);
	printf("configuration completed....\n");
	return 0;
}

int receive(int fd)
{
	printf("communication starts....\n");
	char buffer[1024],rdbuf[255],a,b;
	printf("Enter data to transfer:\n");
	scanf("%s",rdbuf);
	int i;
	fcntl(fd,F_SETFL,0);
	for(i=0;rdbuf[i];i++);
	rdbuf[i]='\0';
	rdbuf[i++]='\r';
	write(fd,rdbuf,strlen(rdbuf)+1);		
	printf("data written successfully....\n");
	bzero(buffer,255);
	if(read(fd,buffer,sizeof(buffer))==0)
 	{
	 perror("read");
	return 0;	
	}
	printf("Received data:%s\n",buffer);
	printf("serial communication ends....\n");
	return 0 ;
}

int main()
{
	int x=open_port();
	printf("%d\n",x);
	init_serialcom(x);
	receive(x); 
}
 

