#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void increase_month(int *mm, int *yy) {
    (*mm)++;
    if (*mm > 12) {
        (*yy)++;
        *mm = 1;
    }
}

void decrease_month(int *mm, int *yy) {
    (*mm)--;
    if (*mm < 1) {
        (*yy)--;
        if (*yy < 1600) {
            printf("\t\tNo record available for years before 1600.\n");
            return;
        }
        *mm = 12;
    }
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
        return -1; // Invalid month
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
    if (mm < 1 || mm > 12) return "Invalid month";
    if (dd < 1 || dd > getNumberOfDays(mm, yy)) return "Invalid date";
    if (yy < 1600) return "Year must be 1600 or later";
    return getName(getDayNumber(dd, mm, yy));
}

void print_date(int mm, int yy) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    printf("\n\t\t-----------------------------\n");
    printf("\t\t      %s, %d", months[mm - 1], yy);
    printf("\n\t\t-----------------------------\n");
}

void printMonth(int mon, int year) {
    int nod = getNumberOfDays(mon, year);
    int day = getDayNumber(1, mon, year);
    print_date(mon, year);
    printf("\t\tSun Mon Tue Wed Thu Fri Sat\n");
    for (int i = 0; i < day; i++) printf("\t\t    ");
    for (int d = 1; d <= nod; d++) {
        printf("\t\t%3d ", d);
        if ((day + d) % 7 == 0) printf("\n");
    }
    printf("\n");
}

void AddNote() {
    FILE *fp = fopen("note.dat", "ab+");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    while (1)
    {
        printf("\t\tEnter the date (DD MM): ");
        scanf("%d %d", &R.dd, &R.mm);
        if (R.dd<=31&&R.mm<=12) break;
    }
    
    printf("\t\tEnter the Note (50 characters max): ");
    getchar(); // Clear newline from input buffer
    fgets(R.note, sizeof(R.note), stdin);
    R.note[strcspn(R.note, "\n")] = 0; // Remove newline from input
    if (fwrite(&R, sizeof(R), 1, fp)) {
        printf("\t\tNote saved successfully.\n");
    } else {
        printf("\t\tFailed to save the note.\n");
    }
    fclose(fp);
}

void showNote() {
    FILE *fp = fopen("note.dat", "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    int isFound = 0;
    while (fread(&R, sizeof(R), 1, fp)) {
        printf("\t\tDate: %02d/%02d - Note: %s\n", R.dd, R.mm, R.note);
        isFound = 1;
    }
    if (!isFound) printf("\t\tNo notes found.\n");
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n\t\t1. Find Out the Day\n\t\t2. Print Month\n\t\t3. Add Note\n\t\t4. Show Notes\n\t\t5. Exit\n\t\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("\t\tEnter date (DD MM YYYY): ");
            scanf("%d %d %d", &date.dd, &date.mm, &date.yy);
            printf("\t\tDay: %s\n", getDay(date.dd, date.mm, date.yy));
            break;
        case 2:
            printf("\t\tEnter month and year (MM YYYY): ");
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
            return 0;
        default:
            printf("\t\tInvalid choice. Try again.\n");
        }
    }
    return 0;
}
