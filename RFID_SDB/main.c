#include "header.h"

#define SCREEN_WIDTH 80 // Define the width of the terminal screen

void print_centered(const char *str) {
    int len = strlen(str);
    int padding = (SCREEN_WIDTH - len) / 2;
    if (padding > 0) {
        printf("%*s%s\n", padding, "", str);
    } else {
        printf("%s\n", str);
    }
}

int main() {
    char ch;
    char rfid[256];
    SDB *hptr = NULL; 
    read_records_from_file(&hptr);
    do {
        system("clear");
        printf("\n");
        print_centered("+-------------------------------+");
        print_centered("| STUDENT RECORD MENU           |");
        print_centered("+-------------------------------+");
        print_centered("| a/A : Add New Record          |");
        print_centered("| s/S : Scan the student        |");
        print_centered("| e/E : Exit                    |");
        print_centered("+-------------------------------+");
        print_centered(" Enter Your Choice: ");

        scanf(" %c", &ch);

        switch (tolower(ch)) {
            case 's':
                strncpy(rfid, scanning(), 13);
                rfid[12] = '\0';
                printf("RFID - %s\n", rfid);
		sleep(1);
                student(&hptr, rfid);
                break;
            case 'a':
                print_centered("\n\t\t Add your Data :\n\n");
                add_new_record(&hptr);
                display_students_list(hptr);
                break;
            case 'e':
                Save_record(hptr);
                usleep(50000);
                print_centered("Exitting...");
                usleep(50000);
                exit(0);
            default:
                print_centered("Invalid option");
                break;
        }
        
        print_centered("Do you want to try again? (y/n): ");
        scanf(" %c", &ch);
    } while (tolower(ch) == 'y');

    return 0;
}

void student(SDB **ptr, char *rfid) {
    char ch;
    do {
        if (*ptr == NULL) {
            print_centered("\n\tNo records found.\n");
            return;
        }
        system("clear");
        if (display_student_list(*ptr, rfid) != 1) return;

        printf("\n");
        print_centered("+-------------------------------+");
        print_centered("| STUDENT RECORD MENU           |");
        print_centered("+-------------------------------+");
        print_centered("| m/M : Modify A Record         |");
        print_centered("| d/D : Delete A Record         |");
        print_centered("| e/E : Exit                    |");
        print_centered("+-------------------------------+");
        print_centered(" Enter Your Choice: ");

        scanf(" %c", &ch);

        switch (tolower(ch)) {
            case 'm':
                print_centered("\t Modify A Record");
                Modify_record(ptr, rfid);
                system("clear");
                display_student_list(*ptr, rfid);
                break;
            case 'd':
                print_centered("\t Delete A Record");
                Delete_record(ptr, rfid);
                break;
            case 'e':
                Save_record(*ptr);
                usleep(50000);
                print_centered("\t Exitting...");
                usleep(50000);
                return;
            default:
                print_centered("\t Invalid option");
                break;
        }

        print_centered("\t Do you want to stay here? (y/n): ");
        scanf(" %c", &ch);
    } while (tolower(ch) == 'y');
}
