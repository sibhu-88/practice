#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct sdb{
	int rollno;
	char name[20];
	int percentage;
	struct sdb *next;
} SDB;

void Add_new_record(SDB **);
void Delete_record(SDB **);
void Show_list(SDB *);
void Modify_record(SDB **);
void Save_record(SDB *);
void Sort_list(SDB *);
void Delete_all_record(SDB **);
void Reverse_list(SDB **);
