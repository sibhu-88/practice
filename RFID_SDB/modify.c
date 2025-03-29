#include "header.h"

#define SCREEN_WIDTH 80 // Define the width of the terminal screen

void Modify_record(SDB **ptr, char *RFID) {
    int percentage;
    char op, name[20];
    char input[100];

    system("clear");
    if (*ptr == NULL) {
        print_centered("\n\tNo records found.\n");
        return;
    }

	if(display_student_list(*ptr, RFID)!=1) return;

    printf("\n");
    print_centered("+--------------------------------------------+");
    print_centered("|        MODIFY OPTIONS MENU                 |");
    print_centered("+--------------------------------------------+");
    print_centered("| N/n : Name                                 |");
    print_centered("| P/p : Percentage                           |");
    print_centered("+--------------------------------------------+");
    print_centered(" Enter Your Choice: ");
    
    scanf(" %c", &op);

    SDB *current = *ptr;
    SDB *previous = NULL;

    while (current != NULL && strncmp(current->RFID, RFID, 12) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        print_centered("Record not found.");
        return;
    }

    percentage = current->percentage;
    strcpy(name, current->name);

    switch (tolower(op)) {
        case 'n':
            print_centered("\t Enter your name: ");
            scanf(" %[^\n]", name);
            break;

        case 'p':
            print_centered("\t Enter your percentage: ");
            while (scanf("%d", &percentage) != 1) {
                print_centered("Invalid input. Please enter a valid percentage: ");
                while (getchar() != '\n'); // Clear the input buffer
            }
            break;

        default:
            print_centered("\t Invalid option selected.");
            return;
    }

    current->percentage = percentage;
    strcpy(current->name, name);

    print_centered("\t Record updated successfully.");
    sleep(1);
}
