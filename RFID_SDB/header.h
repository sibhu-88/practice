#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include<fcntl.h>
#include<termios.h>

typedef struct SDB {

    char RFID[13];
    int rollno;
    char name[50];
    float percentage;
    struct SDB *next;
} SDB;

char *scanning();
void add_new_record(SDB **ptr);
void display_student_list(SDB *ptr, char *RFID);
void display_students_list(SDB *ptr);
