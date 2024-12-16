#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

// ANSI color codes
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define DEFAULT "\033[0m"

int main() {
	int op, cp, user = 0, computer = 0;
	char ch;

	srand(time(0));
	
    system("clear");
	while (1) {
		printf(WHITE "\n\tUser = %d\tComputer = %d\n\n" DEFAULT, user, computer);
		printf(YELLOW "\t1) ROCK\n\t2) PAPER\n\t3) SCISSORS\n\tENTER THE OPTION : " DEFAULT);

		if (scanf("%d", &op) != 1) {
			printf(RED "\nInvalid input. Please enter a number (1-3).\n" DEFAULT);
			while (getchar() != '\n'); // Clear input buffer
			usleep(1500000);
			continue; // Restart loop
		}

		if (op < 1 || op > 3) {
			printf(RED "\nInvalid option. Please choose 1, 2, or 3.\n" DEFAULT);
			usleep(1500000);
			continue;
		}

		cp = rand() % 100;
		cp = cp <= 33 ? 1 : (cp > 66 ? 3 : 2);

		printf(CYAN "\n\tYour choice: " DEFAULT);
		switch (op) {
		case 1:
			printf(CYAN "ROCK\n" DEFAULT);
			break;
		case 2:
			printf(CYAN "PAPER\n" DEFAULT);
			break;
		case 3:
			printf(CYAN "SCISSORS\n" DEFAULT);
			break;
		}
		printf(MAGENTA "\tComputer's choice: " DEFAULT);
		switch (cp) {
		case 1:
			printf(MAGENTA "ROCK\n" DEFAULT);
			break;
		case 2:
			printf(MAGENTA "PAPER\n" DEFAULT);
			break;
		case 3:
			printf(MAGENTA "SCISSORS\n" DEFAULT);
			break;
		}

		usleep(1000000); // Delay after choices are shown

		if (cp == op) {
			printf(BLUE "\n\t\t\tIt's a DRAW!\n" DEFAULT);
		} else if (((cp == 1) && (op == 2)) || ((cp == 2) && (op == 3)) || ((cp == 3) && (op == 1))) {
			user++;
			printf(GREEN "\n\t\t\tYou WIN this round!\n" DEFAULT);
		} else {
			computer++;
			printf(RED "\n\t\t\tComputer WINS this round!\n" DEFAULT);
		}

		if (user == 3) {
			printf(GREEN "\n\t\t\t\tUser = %d\n\t\t\tYou WON the MATCH!\n" DEFAULT, user);
			printf(WHITE "\n\tPress any key to continue (or 'q' to quit): " DEFAULT);
    		scanf(" %c", &ch);
    		if (toupper(ch) == 'Q') {
    			break; // Exit game loop
    		}
		} else if (computer == 3) {
			printf(RED "\n\t\t\t\tComputer = %d\n\t\t\tComputer WON the MATCH!\n" DEFAULT, computer);
			printf(WHITE "\n\tPress any key to continue (or 'q' to quit): " DEFAULT);
    		scanf(" %c", &ch);
    		if (toupper(ch) == 'Q') {
    			break; // Exit game loop
    		}
		}
	}
	printf(WHITE "Thanks for playing!\n" DEFAULT);
	return 0;
}
