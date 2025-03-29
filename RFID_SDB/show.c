#include "header.h"

void display_students_list(SDB *ptr) {
    if (ptr == NULL) {
        printf("\n\tNo records found.\n");
        return;
    }

    printf("\n");
    printf("\t+--------------+---------+---------------------+-------------+\n");
    printf("\t|                 STUDENTS LIST                              |\n");
    printf("\t+--------------+---------+---------------------+-------------+\n");
    printf("\t| RFID         | Roll.No | Name                | Percentage  |\n");
    printf("\t+--------------+---------+---------------------+-------------+\n");

    while (ptr != NULL) {
        printf("\t| %-12s | %-7d | %-19s | %-11.2f |\n", ptr->RFID, ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }
    printf("\t+--------------+---------+---------------------+-------------+\n\n");

}

int display_student_list(SDB *ptr, char *RFID) {
    if (ptr == NULL) {
        printf("\n\tNo records found.\n");
        return 0;
    }

    
    int found = 0;
    while (ptr != NULL) {
        if (strncmp(ptr->RFID, RFID, 12) == 0) {
		printf("\n");
		printf("\t+---------+---------------------+-------------+\n");
		printf("\t|               STUDENT Record                |\n");
		printf("\t+---------+---------------------+-------------+\n");
		printf("\t| Roll.No | Name                | Percentage  |\n");
		printf("\t+---------+---------------------+-------------+\n");
		printf("\t| %-7d | %-21s | %-11.2f |\n", ptr->rollno, ptr->name, ptr->percentage);
		printf("\t+---------+---------------------+-------------+\n\n");
            found = 1;
	    break;
        }
        ptr = ptr->next;
    }

    if (!found) {
        printf("\n\n\tNo matching records found for RFID: %s \n\n", RFID);
	return 0;
    }
	return 1;

}
