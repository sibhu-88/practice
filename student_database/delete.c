#include "header.h"

// Function to delete a record by roll number or name
void delete_record(SDB **ptr) {
    if (*ptr == NULL) {
        printf("No more data to delete.\n");
        return;  // Exit if there are no records
    }

    char option;
    display_delete_menu();
    scanf(" %c", &option);
    option = tolower(option);

    switch (option) {
        case 'r':
            delete_record_by_roll_number(ptr);
            break;
        case 'n':
            delete_record_by_name(*ptr);
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

// Function to delete all records in the linked list
void delete_all_records(SDB **ptr) {
    if (*ptr == NULL) {
        printf("No records to delete. The list is already empty.\n");
        return;
    }

    SDB *current = *ptr; // Pointer to traverse the list
    SDB *nextNode = NULL; // Pointer to hold the next node

    // Traverse the list and free each node
    while (current != NULL) {
        usleep(500); // Optional delay for better visibility during deletion
        nextNode = current->next; // Save the next node
        printf("Deleting record with Roll.No: %d\n", current->rollno);
        free(current); // Free the current node
        current = nextNode; // Move to the next node
    }

    // After all nodes are deleted, set the head to NULL
    *ptr = NULL;
    printf("All records have been deleted successfully.\n");
}

// Function to delete a record by name
void delete_record_by_name(SDB *ptr) {
    char input_name[50];  // Increased size for longer names
    printf("\n\tEnter the name: ");
    scanf(" %[^\n]", input_name); // Read until newline

    // Convert input name to lowercase for case-insensitive comparison
    for (int i = 0; input_name[i]; i++) {
        input_name[i] = tolower(input_name[i]);
    }

    printf("\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");
    int found = 0;  // Flag to check if any records are found

    SDB *current = ptr;
    while (current != NULL) {
        // Convert the name in the list to lowercase for comparison
        char temp_name[50];
        strcpy(temp_name, current->name);
        for (int i = 0; temp_name[i]; i++) {
            temp_name[i] = tolower(temp_name[i]);
        }

        // Compare names
        if (strcmp(temp_name, input_name) == 0) {
            printf("\t| %-7d | %-21s | %-11.2f |\n", current->rollno, current->name, current->percentage);
            found = 1;  // Set flag if a match is found
        }
        current = current->next; // Move to the next record
    }

    if (!found) {
        printf("No records found with the name: %s\n", input_name);
    }

    // Continue to roll number deletion
    delete_record_by_roll_number(&ptr);
}

// Function to delete a record by roll number
void delete_record_by_roll_number(SDB **ptr) {
    int rollno;
    printf("\n\tEnter the Roll No: ");
    scanf("%d", &rollno);

    SDB *current = *ptr;
    SDB *previous = NULL;

    // Search for the record with the matching roll number
    while (current != NULL && current->rollno != rollno) {
        previous = current;
        current = current->next;
    }

    // If the record is found
    if (current != NULL) {
        if (previous == NULL) {
            // Deleting the first node (head)
            *ptr = current->next;
        } else {
            // Deleting a node in the middle or end
            previous->next = current->next;
        }

        free(current);
        usleep(500);
        printf("Roll No: %d deleted successfully.\n", rollno);

        // Adjust roll numbers for the remaining records
        SDB *temp = previous ? previous->next : *ptr;
        while (temp != NULL) {
            temp->rollno -= 1;
            temp = temp->next;
        }
    } else {
        usleep(500);
        printf("Roll No: %d not found!\n", rollno);
    }

    sleep(1);
}

