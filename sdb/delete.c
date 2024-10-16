#include "header.h"

// Function to delete a record by roll number or name
void Delete_record(SDB **ptr){
    char op;

    menu2();
    scanf(" %c", &op);

    op = tolower(op);

    switch(op) {
        case 'r': 
            rollno(ptr); 
            break;
        case 'n': 
            name(*ptr); 
            rollno(ptr); 
            break;
    }
}

// Function to delete all records (currently a placeholder)
void Delete_all_record(SDB **ptr){
    SDB *current = *ptr;
    SDB *nextNode = NULL;

    // Traverse the list and free each node
    while (current != NULL) {
	usleep(500);
        nextNode = current->next;  // Save the next node
        printf("Deleting record with Roll.No: %d\n", current->rollno);
        free(current);             // Free the current node
        current = nextNode;        // Move to the next node
    }

    // After all nodes are deleted, set the head to NULL
    *ptr = NULL;
    printf("All records have been deleted successfully.\n");
}

// Function to handle deletion by name
void name(SDB *ptr) {
    char input_name[20];
    printf("\n\tEnter your name: ");
    scanf(" %[^\n]", input_name);  // Fixed to correctly read until a newline

    // Convert input name to lowercase
    for (int i = 0; input_name[i]; i++) {
        input_name[i] = tolower(input_name[i]);
    }

    printf("\tRoll.No\t\tName\t\tPercentage\n");

    SDB *current = ptr;
    while (current != NULL) {
        // Convert the name in the list to lowercase for case-insensitive comparison
        char temp_name[20];
        strcpy(temp_name, current->name);
        for (int i = 0; temp_name[i]; i++) {
            temp_name[i] = tolower(temp_name[i]);
        }

        // Compare names
        if (strcmp(temp_name, input_name) == 0) {
            printf("\t%d\t\t%s\t\t%d\n", current->rollno, current->name, current->percentage);
        }
        current = current->next;  // Move to the next record in the list
    }

	sleep(1);
}

// Function to delete a record by roll number
void rollno(SDB **ptr) {
    int rollno;

    printf("\n\tEnter your Rollno : ");
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
        printf("Roll no: %d is Deleted Successfully\n", rollno);

        // Adjust roll numbers for the remaining records
        SDB *temp = previous->next;
        while (temp != NULL) {
            temp->rollno -= 1;
            temp = temp->next;
        }
    } else {
	usleep(500);
        printf("Roll no: %d not found!\n", rollno);
    }

	sleep(1);
}

