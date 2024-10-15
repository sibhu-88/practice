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

void menu1(){

	printf("\n\t****STUDENT RECORD MENU****\n\n");
	printf("\t  a/A : Add New Record\n");
	printf("\t  d/D : Delete A Record\n");
	printf("\t  s/S : Show The List\n");
	printf("\t  m/M : Modify A Record\n");
	printf("\t  v/V : Save\n");
	printf("\t  e/E : Exit\n");
	printf("\t  t/T : Sort The List\n");
	printf("\t  l/L : Delete All The Records\n");
	printf("\t  r/R : Reverse The List\n\n");
	printf("\t  Enter Your Choice : ");
}

void menu2(){
	printf("\t  R/r : Enter Roll To Delete\n");
        printf("\t  N/n : Enter Name To Delete\n");
	printf("\t  Enter : ");
}

void menu3(){
	printf("\t  Enter Which Record To Search Fo Nodification\n");
	printf("\t  R/r : To Search A RollNo\n");
        printf("\t  N/n : To Search A Name\n");
	printf("\t  P/P : To Search A percentage\n");
        printf("\t  Enter : ");
}

void menu4(){
	printf("\t  S/s : Save And Exit\n");
        printf("\t  E/e : Exit Without Saving\n");
        printf("\t  Enter : ");
}

void menu5(){
        printf("\t  N/n : Sort With Name\n");
	printf("\t  P/p : Sort With Percentage\n");
	printf("\t  Enter : ");
}
