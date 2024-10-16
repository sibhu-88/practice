#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct sdb{
	int rollno;
	char name[20];
	int percentage;
	struct sdb *next;
} SDB;

void menu1(void);
void menu2(void);
void menu3(void);
void menu4(void);
void menu5(void);

void Add_new_record(SDB **);
void Delete_record(SDB **);

void name(SDB *);
void rollno(SDB **);

void src_name(SDB **,int);
void print(SDB **,int);
void src_percentage(SDB **,int);

void Show_list(SDB *);
void Modify_record(SDB **);
void Save_record(SDB *);
void Sort_list(SDB *);
void Delete_all_record(SDB **);
void Reverse_list(SDB *);
void Exit(SDB *);

int count(SDB *);
