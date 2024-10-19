#include "header.h"

// Function to display the list of student records
void display_student_list(SDB *ptr) {
    if (ptr == NULL) {
        printf("\n\tNo records found.\n");
        return;
    }

    printf("\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| SHOWING LIST :                 		      |\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");

    while (ptr != NULL) {
        printf("\t| %-7d | %-21s | %-11.2f |\n", ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }
    printf("\t+---------+-----------------------+-------------+\n");

    char choice;
    printf("\n\tDo you want to quit? ( y ): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        return;
    }
}

// Function to sort the student records
void sort_student_list(SDB *ptr) {
    if (ptr == NULL) {
        printf("\n\tNo records to sort.\n");
        return;
    }

    char option;
    int length = count_records(ptr);
    SDB **arr = (SDB **)malloc(length * sizeof(SDB *));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    SDB *temp = ptr;
    for (int i = 0; temp != NULL; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    display_sort_menu();
    scanf(" %c", &option);
    option = tolower(option);

    switch (option) {
        case 'n':
            sort_by_name(arr, length); // Match header declaration
            break;
        case 'p':
            sort_by_percentage(arr, length); // Match header declaration
            break;
        default:
            printf("Invalid option.\n");
            free(arr);
            return;
    }

    print_sorted_records(arr, length); // Ensure it matches the header declaration
    free(arr);

    char choice;
    printf("\n\tDo you want to quit? ( y ): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        return;
    }
}

// Implementations of sort_by_name, sort_by_percentage, and print_sorted_records...


// Function to reverse the order of student records
void reverse_student_list(SDB *ptr) {
    if (ptr == NULL) {
        printf("\n\tNo records to reverse.\n");
        return;
    }

    int length = count_records(ptr);
    SDB **arr = (SDB **)malloc(length * sizeof(SDB *));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    SDB *temp = ptr;
	for (int i = 0; i < length; i++) {
	    arr[i] = temp; // Use i directly
	    if (temp != NULL) {
	        temp = temp->next; // Move to the next node
	    }
	}
    printf("\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| REVERSED LIST :                               |\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");
    
    for (int i = length - 1; i >= 0; i--) {
        printf("\t| %-7d | %-21s | %-11.2f |\n", arr[i]->rollno, arr[i]->name, arr[i]->percentage);
    }
    printf("\t+---------+-----------------------+-------------+\n");

    // Ask if the user wants to quit
    char choice;
    printf("\n\tDo you want to quit? (y): ");
    scanf(" %c", &choice);
    if (tolower(choice) == 'y') {
        free(arr);
        return;
    }

    free(arr);
}

// Function to sort by percentage
void sort_by_percentage(SDB **arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (arr[j]->percentage > arr[j + 1]->percentage) {
                SDB *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort by name
void sort_by_name(SDB **arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (strcmp(arr[j]->name, arr[j + 1]->name) > 0) {
                SDB *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print sorted records
void print_sorted_records(SDB **arr, int length) {
    printf("\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| SORTED LIST :                                 |\n");
    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");

    for (int i = 0; i < length; i++) {
        if (arr[i] != NULL) {
            printf("\t| %-7d | %-21s | %-11.2f |\n", arr[i]->rollno, arr[i]->name, arr[i]->percentage);
        } else {
            printf("\tNo record at index %d\n", i);
        }
    }
    printf("\t+---------+-----------------------+-------------+\n");
}

