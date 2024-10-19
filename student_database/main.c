#include "header.h"

int main() {
    char option;
    SDB *headPtr = NULL;

    // Load records from file
    read_records_from_file(&headPtr);

    while (1) {
        // Clear the terminal screen (platform-dependent)
        system("clear"); 
        display_main_menu(); // Display the main menu

        // Get user input
        scanf(" %c", &option);
        option = tolower(option); // Normalize input

        // Handle user input
        switch (option) {
            case 'a':
                add_new_record(&headPtr);
                break;
            case 'd':
                delete_record(&headPtr);
                break;
            case 's':
                display_student_list(headPtr);
                break;
            case 'm':
                modify_record(&headPtr);
                break;
            case 'v':
                save_records(headPtr);
                break;
            case 'e':
                exit_program(headPtr);
                break;
            case 't':
                sort_student_list(headPtr);
                break;
            case 'l':
                delete_all_records(&headPtr);
                break;
            case 'r':
                reverse_student_list(headPtr);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        sleep(1); // Pause for a moment before the next iteration
    }

    // Free allocated memory (if necessary)
    delete_all_records(&headPtr); // Clean up before exiting
    return 0; // Exit the program
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
        sscanf(line, "%d\t%[^\t]\t%f", &temp->rollno, name, &temp->percentage);
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

// Function to count the number of records in the linked list
int count_records(SDB *ptr) {
    int count = 0;
    while (ptr != NULL) {
        ptr = ptr->next; // Move to the next record
        count++;
    }
    return count;
}

// Function to handle program exit with optional save
void exit_program(SDB *ptr) {
    char option;
    display_exit_menu(); // Use the standardized exit menu
    scanf(" %c", &option);
    option = tolower(option);

    switch (option) {
        case 's':
            save_records(ptr); // Save records before exiting
            break;
        case 'e':
            break; // Just exit without saving
        default:
            printf("Invalid option. Exiting without action.\n");
            break;
    }

    printf("Exiting the Student Database. Goodbye!\n");
    // Free allocated memory before exiting
    delete_all_records(&ptr);
    exit(0); // Terminate the program
}

// Display functions
void display_main_menu() {
    printf("\n");
    printf("\t---------------------------------\n");
    printf("\t| STUDENT RECORD MENU           |\n");
    printf("\t---------------------------------\n");
    printf("\t| a/A : Add New Record          |\n");
    printf("\t| d/D : Delete A Record         |\n");
    printf("\t| s/S : Show The List           |\n");
    printf("\t| m/M : Modify A Record         |\n");
    printf("\t| v/V : Save                    |\n");
    printf("\t| e/E : Exit                    |\n");
    printf("\t| t/T : Sort The List           |\n");
    printf("\t| l/L : Delete All              |\n");
    printf("\t| r/R : Reverse The List        |\n");
    printf("\t---------------------------------\n");
    printf("\t Enter Your Choice: ");
}


void displayDeleteMenu() {
    printf("\n");
    printf("\t---------------------------------\n");
    printf("\t| DELETE RECORD MENU            |\n");
    printf("\t---------------------------------\n");
    printf("\t| R/r : Enter Roll Number       |\n");
    printf("\t| N/n : Enter Name              |\n");
    printf("\t---------------------------------\n");
    printf("\t Enter Your Choice: ");
}

void displayModifyMenu() {
    printf("\n");
    printf("\t---------------------------------\n");
    printf("\t| MODIFY RECORD MENU            |\n");
    printf("\t---------------------------------\n");
    printf("\t| R/r : Search By Roll Number   |\n");
    printf("\t| N/n : Search By Name          |\n");
    printf("\t| P/p : Search By Percentage    |\n");
    printf("\t---------------------------------\n");
    printf("\t Enter Your Choice: ");
}


// Function to display the exit menu
void display_exit_menu() {
    printf("\n");
    printf("\t---------------------------------\n");
    printf("\t| EXIT CONFIRMATION MENU        |\n");
    printf("\t---------------------------------\n");
    printf("\t| S/s : Save And Exit           |\n");
    printf("\t| E/e : Exit Without Saving     |\n");
    printf("\t---------------------------------\n");
    printf("\t Enter Your Choice: ");
}

void displaySortMenu() {
    printf("\n");
    printf("\t---------------------------------\n");
    printf("\t| SORT RECORD MENU              |\n");
    printf("\t---------------------------------\n");
    printf("\t| N/n : Sort By Name            |\n");
    printf("\t| P/p : Sort By Percentage      |\n");
    printf("\t---------------------------------\n");
    printf("\t Enter Your Choice: ");
}

void displayModifyOptionsMenu() {
    printf("\n");
    printf("\t----------------------------------------------\n");
    printf("\t| MODIFY OPTIONS MENU                        |\n");
    printf("\t----------------------------------------------\n");
    printf("\t| N/n : Modify Name Only                     |\n");
    printf("\t| P/p : Modify Percentage Only               |\n");
    printf("\t| B/b : Modify Both Name and Percentage      |\n");
    printf("\t----------------------------------------------\n");
    printf("\t Enter Your Choice: ");
}

