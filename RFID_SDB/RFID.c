#include "header.h"

char *scanning()
{
	int serial_port=open("/dev/ttyUSB0",O_RDWR);
	
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

	char *rdbuf = malloc(256);
	int scan = 1;

	printf("Scanning the Id.......\n");

	while (scan) {	
		memset(rdbuf, 0, 256); 	
		int bytes_read = read(serial_port, rdbuf, 256);	
		if (bytes_read == 12) {
		    rdbuf[bytes_read] = '\0';
	 	    close(serial_port);
		    sleep(1);
		    return rdbuf;
	 	} else {
		    sleep(1);
		    printf("Scan again...\n");
		}
	}
	close(serial_port);
	free(rdbuf);
	return NULL;
}
