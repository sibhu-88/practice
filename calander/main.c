#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Color macros for ANSI escape codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BLUE "\033[34m"

struct Date {
    int dd;
    int mm;
    int yy;
};
struct Date date;

struct Remainder {
    int dd;
    int mm;
    char note[50];
};
struct Remainder R;

int check_leapYear(int year) {
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

int getNumberOfDays(int month, int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return check_leapYear(year) ? 29 : 28;
    default:
        return -1;
    }
}

char *getName(int day) {
    switch (day) {
    case 0: return "Sunday";
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    default: return "Invalid Day";
    }
}

int getDayNumber(int day, int mon, int year) {
    int res = 0, t1, t2, y = year;
    year -= 1600;
    while (year >= 100) {
        res += 5;
        year -= 100;
    }
    res = res % 7;
    t1 = (year - 1) / 4;
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    res += t1 % 7;
    t2 = 0;
    for (t1 = 1; t1 < mon; t1++) {
        t2 += getNumberOfDays(t1, y);
    }
    t2 += day;
    res += t2 % 7;
    if (y > 2000) res++;
    return res % 7;
}

char *getDay(int dd, int mm, int yy) {
    if (mm < 1 || mm > 12) return RED "Invalid month" RESET;
    if (dd < 1 || dd > getNumberOfDays(mm, yy)) return RED "Invalid date" RESET;
    if (yy < 1600) return RED "Year must be 1600 or later" RESET;
    return getName(getDayNumber(dd, mm, yy));
}

void printMonth(int mon, int year) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    int nod = getNumberOfDays(mon, year);
    int day = getDayNumber(1, mon, year);

    printf(CYAN "\n\t\t -----------------------------------\n");
    printf("\t\t            %s, %d", months[mon - 1], year);
    printf("\n\t\t -----------------------------------\n" RESET);

    printf(YELLOW "\t\t  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n" RESET);
    for (int i = 0; i < day; i++) printf("    ");
    printf("\t\t");
    for (int d = 1; d <= nod; d++) {
        printf(" %3d ", d);
        if ((day + d) % 7 == 0) printf("\n\t\t");
    }
    printf("\n");
}

void AddNote() {
    FILE *fp = fopen("note.dat", "ab+");
    if (!fp) {
        perror(RED "Error opening file" RESET);
        return;
    }
    do {
        printf(GREEN "Enter the date (DD MM): " RESET);
        scanf("%d %d", &R.dd, &R.mm);
    } while (R.dd < 1 || R.dd > 31 || R.mm < 1 || R.mm > 12);

    printf(GREEN "Enter the Note (50 characters max): " RESET);
    getchar();
    fgets(R.note, sizeof(R.note), stdin);
    R.note[strcspn(R.note, "\n")] = 0;

    if (fwrite(&R, sizeof(R), 1, fp)) {
        printf(GREEN "Note saved successfully.\n" RESET);
    } else {
        printf(RED "Failed to save the note.\n" RESET);
    }
    fclose(fp);
}

void showNote() {
    FILE *fp = fopen("note.dat", "rb");
    if (!fp) {
        perror(RED "Error opening file" RESET);
        return;
    }
    int isFound = 0;
    printf(CYAN "\t\tNotes:\n" RESET);
    while (fread(&R, sizeof(R), 1, fp)) {
        printf(YELLOW "\t\tDate: %02d/%02d - Note: %s\n" RESET, R.dd, R.mm, R.note);
        isFound = 1;
    }
    if (!isFound) printf(RED "\t\tNo notes found.\n" RESET);
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf(CYAN "\n\t\t1. Find Out the Day\n\t\t2. Print Month\n\t\t3. Add Note\n\t\t4. Show Notes\n\t\t5. Exit\n" RESET);
        printf(GREEN "\t\tEnter your choice: " RESET);
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf(GREEN "Enter date (DD MM YYYY): " RESET);
            scanf("%d %d %d", &date.dd, &date.mm, &date.yy);
            printf(YELLOW "\n\t\tDay: %s\n" RESET, getDay(date.dd, date.mm, date.yy));
            break;
        case 2:
            printf(GREEN "Enter month and year (MM YYYY): " RESET);
            scanf("%d %d", &date.mm, &date.yy);
            printMonth(date.mm, date.yy);
            break;
        case 3:
            AddNote();
            break;
        case 4:
            showNote();
            break;
        case 5:
            printf(GREEN "\t\tExiting... Goodbye!\n" RESET);
            return 0;
        default:
            printf(RED "\t\tInvalid choice. Try again.\n" RESET);
        }
    }
}