#include "header.h"

// Function to add a new record to the linked list
void add_new_record(SDB **ptr) {
    char choice;

    do {
        // Allocate memory for a new record
        SDB *newRecord = (SDB *)malloc(sizeof(SDB));
        if (newRecord == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return; // Exit if memory allocation fails
        }

        // Get user input for the new record
        printf("\tEnter Your Name: ");
        scanf(" %[^\n]", newRecord->name);

        printf("\tEnter Your Percentage: ");
        while (scanf("%f", &newRecord->percentage) != 1 || newRecord->percentage < 0 || newRecord->percentage > 100) {
            printf("\tInvalid input. Please enter a valid percentage (0-100): ");
            while(getchar() != '\n'); // Clear the invalid input
        }

        // If the list is empty, initialize the first record
        if (*ptr == NULL) {
            newRecord->rollno = 1; // Set roll number for the first record
            newRecord->next = NULL; // No next record
            *ptr = newRecord; // Update the head pointer
        } else {
            // Traverse to the end of the list to add the new record
            SDB *last = *ptr;
            while (last->next != NULL) {
                last = last->next; // Move to the next record
            }

            // Assign roll number and link the new record
            newRecord->rollno = last->rollno + 1; // Increment roll number
            newRecord->next = NULL; // New record will be the last
            last->next = newRecord; // Link the last record to the new one
        }

        // Ask user if they want to add another record
        printf("\tDo you want to add another record? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y'); // Continue if 'y' or 'Y' is entered
}

