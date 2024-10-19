#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Define the SDB structure for student records
typedef struct sdb {
    int rollno;                // Student roll number
    char name[50];             // Student name (increased size for longer names)
    float percentage;          // Student percentage
    struct sdb *next;         // Pointer to the next record
} SDB;

// Function declarations

// Menu functions
void display_main_menu(void);
void display_delete_menu(void);
void display_modify_menu(void);
void display_exit_menu(void);
void display_sort_menu(void);
void display_modify_options_menu(void);

// Record management functions
void add_new_record(SDB **head);
void read_records_from_file(SDB **head);
void delete_record(SDB **head);
void save_records(SDB *head);
void delete_all_records(SDB **head);

// Search and sorting functions
void sort_by_name(SDB **head, int length);
void sort_by_percentage(SDB **head, int length);
void sort_student_list(SDB *head);
void delete_record_by_name(SDB *ptr);
void delete_record_by_roll_number(SDB **ptr);
void print_sorted_records(SDB **arr, int length);

// Display and modification functions
void display_student_list(SDB *head);
void modify_record(SDB **head);
void modify_name(SDB *record);
void modify_percentage(SDB *head);
void modify_roll_number(SDB **record);

// List manipulation functions
void reverse_student_list(SDB *head);
int count_records(SDB *head);
void exit_program(SDB *head);

#endif // HEADER_H

