#include "header.h"

void save_records(SDB *ptr) {  // Change from save_record to save_records
    FILE *file = fopen("student.xls", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    fprintf(file, "Roll.No\tName\tPercentage\n");

    SDB *current = ptr;
    while (current != NULL) {
        fprintf(file, "%d\t%s\t%.2f\n", current->rollno, current->name, current->percentage);
        current = current->next;
    }

    fclose(file);
    printf("File saved successfully as 'student.xls'.\n");
    sleep(1);
}

