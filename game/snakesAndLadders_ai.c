#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

// ANSI color codes
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define DEFAULT "\033[0m"
#define BLACK "\033[1;30m"
#define YELLOW "\033[1;33m"

// Function declarations
void welcome(void);
void printBoard(void);
void check(int *);
bool reset(void);
void delay(int milliseconds); // Delay function

// Global variables
int player1 = 0, player2 = 0;

int main() {
	char ch;
	int num;
	bool playAgain = true;

	srand(time(NULL)); // Seed the random number generator ONCE

	while (playAgain) {
		player1 = player2 = 0;
		welcome();
		printBoard();
		delay(1000); // Initial delay

		while (player1 < 100 && player2 < 100) {
			// Player 1's turn
			printf(RED "#PLAYER1 PRESS ENTER TO ROLL DICE " DEFAULT);
			getchar();
			num = (rand() % 6) + 1;
			printf(RED "#PLAYER1 DICE ROLL: %d\n" DEFAULT, num);
			delay(1000); // Delay after dice roll

			if (player1 + num <= 100) {
				player1 += num;
				check(&player1);
				printBoard();
				delay(1500); // Delay after move
			} else {
				printf("Not enough to move!\n");
				delay(1000);
			}
			if (player1 >= 100) break;

			// Player 2's turn
			printf(BLUE "#PLAYER2 PRESS ENTER TO ROLL DICE " DEFAULT);
			getchar();
			num = (rand() % 6) + 1;
			printf(BLUE "#PLAYER2 DICE ROLL: %d\n" DEFAULT, num);
			delay(1000);

			if (player2 + num <= 100) {
				player2 += num;
				check(&player2);
				printBoard();
				delay(1500);
			} else {
				printf("Not enough to move!\n");
				delay(1000);
			}
		}
		if (player1 >= 100) {
			printf(CYAN "\nPLAYER1 WINS!\n" DEFAULT);
		} else {
			printf(CYAN "\nPLAYER2 WINS!\n" DEFAULT);
		}
		delay(2000); // Delay before asking to play again
		playAgain = reset();
	}
	printf("Thanks for playing!\n");
	return 0;
}

void welcome(void) {
	system("clear");
	printf("\n\t\tWelcome to Snakes and Ladders!\n");
}

void printBoard(void) {
	int val = 100, i,board[100];
	for (i = 0; i < 100; i++)
		board[i] = i + 1;
	for (i = val - 1; i > 0; i--)
	{
		if(player1==player2&&player1-1==i) {
			printf(RED"P"BLUE"P    \033[0m");
		} else if (i == player1-1 && player1 != 0)
			printf(RED"P1    \033[0m");
		else if (i == player2-1 && player2 != 0)
			printf(BLUE"P2    \033[0m");
		else
		{
			if (board[i] == 100)
				printf(BLACK"%d   \033[0m", board[i]);
			else if (board[i] < 10)
				printf(BLACK"%d     \033[0m", board[i]);
			else
				printf(BLACK"%d    \033[0m", board[i]);
		}

		if (board[i] == 100)
			continue;
		if (board[i] % 10 == 1)
		{
			printf("\n");
			val -= 10;
			for (i -= 10; i < val; i++)
			{
				if(player1==player2&&(player1!=0)&&player1-1==i) {
					printf(RED"P"BLUE"P    \033[0m");
				} else if (i == player1-1 && player1 != 0)
					printf(RED"P1    \033[0m");
				else if (i == player2-1 && player2 != 0)
					printf(BLUE"P2    \033[0m");
				else
				{
					if (board[i] == 100)
						printf(BLACK"%d   \033[0m", board[i]);
					else if (board[i] < 10)
						printf(BLACK"%d     \033[0m", board[i]);
					else
						printf(BLACK"%d    \033[0m", board[i]);
				}
			}
			val -= 10;
			i = val;
			printf("\n");
		}
	}
}

void check(int *player) {
	int snakesAndLadders[101] = {0};
	snakesAndLadders[1] = 38;
	snakesAndLadders[4] = 10;
	snakesAndLadders[9] = 22;
	snakesAndLadders[17] = -10;
	snakesAndLadders[21] = 21;
	snakesAndLadders[28] = 56;
	snakesAndLadders[51] = 16;
	snakesAndLadders[62] = -43;
	snakesAndLadders[64] = -4;
	snakesAndLadders[72] = 19;
	snakesAndLadders[80] = 19;
	snakesAndLadders[87] = -51;
	snakesAndLadders[92] = -19;
	snakesAndLadders[95] = -20;
	snakesAndLadders[98] = -19;

	if (*player >= 100) return;

	if (snakesAndLadders[*player] != 0) {
		int p = *player;
		*player += snakesAndLadders[p];
		if (*player < 1) *player = 1;
		if (snakesAndLadders[p] > 0)
			printf(MAGENTA "Player UP from %d to %d through ladder\n" DEFAULT, p, *player);
		else
			printf(YELLOW "Player DOWN from %d to %d through snake\n" DEFAULT, p, *player);
	}
}

bool reset() {
	char op;
	printf("Play again? (y/n): ");
	scanf(" %c", &op);
	return tolower(op) == 'y';
}

// Delay function (cross-platform - improved)
void delay(int milliseconds) {
	usleep(milliseconds * 1000); // usleep takes microseconds
}