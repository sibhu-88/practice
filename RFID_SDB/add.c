#include "header.h"

void add_new_record(SDB **ptr) {
    char choice;

    do {
        SDB *newRecord = (SDB *)malloc(sizeof(SDB));
        if (newRecord == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return;
        }

	
	strncpy(newRecord->RFID,scanning(),13);

        printf("\tEnter Your Name: ");
        scanf(" %[^\n]", newRecord->name);

        printf("\tEnter Your Percentage: ");
	while (scanf("%f", &newRecord->percentage) != 1) {
            printf("Invalid input. Please enter a valid percentage: ");
            while (getchar() != '\n');
        }

        if (*ptr == NULL) {
            newRecord->rollno = 1;
            newRecord->next = NULL;
            *ptr = newRecord;
        } else {
            SDB *last = *ptr;
            while (last->next != NULL) {
                last = last->next;
            }

            newRecord->rollno = last->rollno + 1;
            newRecord->next = NULL;
            last->next = newRecord;
        }

	printf("\t %d  %-7s  %-21s  %-11.2f \n", newRecord->rollno, newRecord->RFID, newRecord->name, newRecord->percentage);

        printf("\tDo you want to add another record? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y'); 
}

