#include "header.h"

void Delete_record(SDB **ptr, char *RFID) {
    if (*ptr == NULL) {
        printf("\n\tNo records found.\n");
        return;
    }

    SDB *current = *ptr;
    SDB *previous = NULL;

    // Find the record with the matching RFID
    while (current != NULL && strncmp(current->RFID, RFID, 12) != 0) {
        previous = current;
        current = current->next;
    }

    // Deleting the first node (head)
    if (previous == NULL) {
        *ptr = current->next; // Move head to the next node
    } else {
        // Deleting a node in the middle or end
        previous->next = current->next;
    }

    // Free the memory of the current node
    free(current);

    // Adjust roll numbers for the remaining records
    current = *ptr; // Reset current to the new head

    printf("\t Your record deleted successfully.\n");
    usleep(500000); // Sleep for 0.5 seconds
	Save_record(*ptr);
	usleep(50000);
}
