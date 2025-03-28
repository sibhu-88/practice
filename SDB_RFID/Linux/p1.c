//LINUX SERIAL PROGRAMMING
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>

int main()
{
	int serial_port=open("/dev/ttyUSB0",O_RDWR);
	FILE* file=fopen("data.ods","w");
	
	struct termios tty;
	tcgetattr(serial_port,&tty);

	tty.c_cflag&=~PARENB;
	tty.c_cflag&=~CSTOPB;
	tty.c_cflag&=~CSIZE;
	tty.c_cflag|=CS8;
	tty.c_cflag&=~CRTSCTS;
	tty.c_cflag|=CREAD|CLOCAL;


	tty.c_cc[VTIME]=10;
	tty.c_cc[VMIN]=19;

	tcsetattr(serial_port,TCSANOW,&tty);

	char rdbuf[256];
	fprintf(file,"SENSOR DATA,DATE,TIME\n");
	int c=4;

	time_t t;
	struct tm* t1;
	char tbuf[256],t1buf[256];
	while(c--)
	{
		bzero(rdbuf,sizeof(rdbuf));
		read(serial_port,rdbuf,sizeof(float));
		
		sleep(3);
		time(&t);
		t1=localtime(&t);
		strftime(tbuf,sizeof(tbuf),"%d-%m-%y",t1);
		strftime(t1buf,sizeof(t1buf),"%H:%M:%S",t1);

		printf(" %s %s %s\n",rdbuf,tbuf,t1buf);
		fprintf(file,"%s  ,%s,%s\n",rdbuf,tbuf,t1buf);
		sleep(3);
	
	}
	close(serial_port);
	fclose(file);
	
	return 0;
}
