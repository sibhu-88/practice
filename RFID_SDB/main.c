#include "header.h"

int main() {
    char ch;
    char rfid[256];
    SDB *hptr = NULL; 
    do {
        system("clear");
        printf("\t\t\tStudents Data Base\n\n");
        printf("\t\t S/s Search the record\n");
        printf("\t\t A/a Add the record\n");
        printf("\t\t L/l Show List\n\n");
        printf("Enter the option: ");
        scanf(" %c", &ch);

        ch = tolower(ch);
        switch (ch) {
            case 's':
                strncpy(rfid, scanning(), 13);
                rfid[12] = '\0';
                printf("RFID - %s\n", rfid);
		display_student_list(hptr,rfid);
                break;
            case 'a':
                printf("Adding the data.\n");
                add_new_record(&hptr);
		display_students_list(hptr);
                break;
            default:
                printf("Invalid option\n");
                break;
        }
	
        printf("Do you want to try again? (y/n): ");
        scanf(" %c", &ch);
    } while (tolower(ch) == 'y');

    return 0;
}
