#include "header.h"

// Function to modify a record based on roll number, name, or percentage
void modify_record(SDB **ptr) {
    char option;

    display_modify_menu();
    scanf(" %c", &option);
    option = tolower(option);

    switch (option) {
        case 'r':
            modify_roll_number(ptr);
            break;
        case 'n':
            modify_name(*ptr);
            modify_roll_number(ptr);
            break;
        case 'p':
            modify_percentage(*ptr);
            modify_roll_number(ptr);
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

// Function to modify a record by name
void modify_name(SDB *ptr) {
    char input_name[50];  // Increased size for longer names
    printf("\n\tEnter the name: ");
    scanf(" %[^\n]", input_name);

    // Convert input name to lowercase for case-insensitive comparison
    for (int i = 0; input_name[i]; i++) {
        input_name[i] = tolower(input_name[i]);
    }

    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");

    SDB *current = ptr;
    while (current != NULL) {
        char temp_name[50];  // Increased size for longer names
        strcpy(temp_name, current->name);
        for (int i = 0; temp_name[i]; i++) {
            temp_name[i] = tolower(temp_name[i]);
        }

        if (strcmp(temp_name, input_name) == 0) {
            printf("\t| %-7d | %-21s | %-11.2f |\n", current->rollno, current->name, current->percentage);
            printf("\t+---------+-----------------------+-------------+\n");
        }
        current = current->next;
    }

    sleep(1);
}

// Function to modify a record by percentage
void modify_percentage(SDB *ptr) {
    float input_percentage;
    printf("\n\tEnter the percentage: ");
    scanf(" %f", &input_percentage);  // Changed to float for precision

    printf("\t+---------+-----------------------+-------------+\n");
    printf("\t| Roll.No | Name                  | Percentage  |\n");
    printf("\t+---------+-----------------------+-------------+\n");

    SDB *current = ptr;
    while (current != NULL) {
        if (input_percentage == current->percentage) {
            printf("\t| %-7d | %-21s | %-11.2f |\n", current->rollno, current->name, current->percentage);
            printf("\t+---------+-----------------------+-------------+\n");
        }
        current = current->next;
    }

    sleep(1);
}

void modify_roll_number(SDB **ptr) {
    int rollno;
    float percentage;
    char option, name[50];  // Increased size for longer names

    printf("\n\tEnter the Roll No: ");
    scanf("%d", &rollno);

    SDB *current = *ptr;

    while (current != NULL && current->rollno != rollno) {
        current = current->next;
    }

    if (current != NULL) {
        while (1) {
            display_modify_options_menu();
            scanf(" %c", &option);
            option = tolower(option);

            switch (option) {
                case 'n':
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", name);
                    strcpy(current->name, name);
                    printf("Name modified successfully.\n");
                    break;

                case 'p':
                    printf("Enter the new percentage: ");
                    scanf("%f", &percentage);
                    current->percentage = percentage;
                    printf("Percentage modified successfully.\n");
                    break;

                case 'b':
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", name);
                    strcpy(current->name, name);
                    printf("Enter the new percentage: ");
                    scanf("%f", &percentage);
                    current->percentage = percentage;
                    printf("Name and percentage modified successfully.\n");
                    break;

                default:
                    printf("Invalid option. Please choose again.\n");
                    continue;  // Go back to the start of the loop
            }
            break;  // Exit after successful modification
        }
    } else {
        printf("Roll No: %d not found!\n", rollno);
    }
}
