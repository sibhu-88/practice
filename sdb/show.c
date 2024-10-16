#include "header.h"

void Show_list(SDB *ptr) {
    printf("\n\tShowing list:\n");
    printf("\tRoll.No\t\tName\t\tPercentage\n");
    while (ptr != NULL) {
        printf("\t%d\t\t%s\t\t%d\n", ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }
}

void Sort_list(SDB *ptr) {
    char op;
    int i = 0;

    int l = count(ptr);
    SDB **arr = (SDB **)malloc(l * sizeof(SDB *));

    SDB *temp = ptr;
    while (temp != NULL) {
        arr[i] = temp; 
        temp = temp->next;
	i++;
    }

    menu5();
    scanf(" %c", &op);

    op = tolower(op);

    switch (op) {
        case 'n':{ src_name(arr, l);
			 print(arr, l);
			 break;
		 }
        case 'p': {src_percentage(arr, l);
			 print(arr, l);
			break;
		  }
        default: printf("Invalid option.\n"); break;
    }

    free(arr);
}

void Reverse_list(SDB *ptr) {
    int l = count(ptr);
    SDB **arr = (SDB **)malloc(l * sizeof(SDB *));
    SDB *temp = ptr;
    int i = 0;

    while (temp != NULL) {
        arr[i++] = temp;
        temp = temp->next;
    }

    printf("\n\tReversed list:\n");
    printf("\tRoll.No\t\tName\t\tPercentage\n");
    for (i = l - 1; i >= 0; i--) {
        printf("\t%d\t\t%s\t\t%d\n", arr[i]->rollno, arr[i]->name, arr[i]->percentage);
    }

    free(arr);
}

void src_percentage(SDB **arr, int l) {
    SDB *temp;
    int i, j;

    for (i = 0; i < l - 1; i++) {
        for (j = 0; j < l - i - 1; j++) {
            if (arr[j]->percentage > arr[j + 1]->percentage) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void src_name(SDB **arr, int l) {
    SDB *temp;
    int i, j;

    for (i = 0; i < l - 1; i++) {
        for (j = 0; j < l - i - 1; j++) {
            if (strcmp(arr[j]->name, arr[j + 1]->name) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print(SDB **arr, int l) {
    printf("\n\tSorted list:\n");
    printf("\tRoll.No\t\tName\t\tPercentage\n");

    for (int i = 0; i < l; i++) {
        if (arr[i] != NULL) { // Check if pointer is not NULL
            printf("\t%d\t\t%s\t\t%d\n", arr[i]->rollno, arr[i]->name, arr[i]->percentage);
        } else {
            printf("\tNo record at index %d\n", i); // This will help identify issues
        }
    }
}

