#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct sdb
{
	int rollno;
	char name[20];
	int percentage;
	struct sdb *next;
} SDB;

