#include "header.h"

void Save_record(SDB *ptr)
{
    FILE *file = fopen("student.xls", "w");
    if (file == NULL)
    {
        perror("Unable to open file");
        return;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "RFID\tRoll.No\tName\tPercentage\n");
    }
    SDB *current = ptr;
    while (current != NULL)
    {
        fprintf(file, "%s\t%d\t%s\t%.1f\n", current->RFID,current->rollno, current->name, current->percentage);
        current = current->next;
    }

    fclose(file);
    sleep(1);
    printf("File Saved successfully..\n");
    sleep(1);
}

void read_records_from_file(SDB **ptr) {
    FILE *file = fopen("student.xls", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file 'student.xls'.\n");
        *ptr = NULL; // File not found
        return;
    }

    char line[256];
    
    // Skip header line
    fgets(line, sizeof(line), file);

    // Read each line and create a new record
    while (fgets(line, sizeof(line), file)) {
        SDB *temp = (SDB *)malloc(sizeof(SDB));
        if (temp == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            fclose(file);
            return;
        }

        char name[50];
        sscanf(line, "%s\t%d\t%[^\t]\t%f",temp->RFID, &temp->rollno, name, &temp->percentage);
        strcpy(temp->name, name);
        temp->next = NULL;

        // Add new record to the linked list
        if (*ptr == NULL) {
            *ptr = temp; // First record
        } else {
            SDB *last = *ptr;
            while (last->next != NULL) {
                last = last->next; // Traverse to the end
            }
            last->next = temp; // Link new record
        }
    }

    fclose(file);
}
