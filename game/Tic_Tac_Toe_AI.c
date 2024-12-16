#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

// ANSI color codes
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define DEFAULT "\033[0m"

void welcome(void);
void printBoard(char*);
bool checkWinner(char*);
bool reset(char *);
void delay(int milliseconds);

int main() {
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int move;
    bool gameOver = false;

    srand(time(NULL));

        welcome();
    while (1) {
        delay(500); // Initial delay

        // Computer's turn
        int computerMove;
        do {
            computerMove = rand() % 9;
        } while (board[computerMove] != ' ');

        board[computerMove] = 'O';
        printf(MAGENTA "\n\t\tComputer's Move\n" DEFAULT);
        printBoard(board);
        delay(1000); // Delay after computer's move

        gameOver = checkWinner(board);
        if (gameOver) {
            if (reset(board)) {
                continue;
            } else {
                break;
            }
        }

        // Player's turn
        do {
            printf(BLUE "\n\t\tEnter Your move (1-9): " DEFAULT);
            if (scanf("%d", &move) != 1) {
                printf(RED "\n\t\tInvalid input. Please enter a number.\n" DEFAULT);
                while (getchar() != '\n');
                delay(1000); // Delay for invalid input
                continue;
            }
            move--;

            if (move < 0 || move > 9) {
                printf(RED "\n\t\tInvalid move. Please enter a number between 1 and 9.\n" DEFAULT);
                delay(1000); // Delay for invalid move
                continue;
            }

            if (board[move] != ' ') {
                printf(RED "\n\t\tAlready occupied! Try again.\n" DEFAULT);
                delay(1000); // Delay for occupied space
            }
        } while (board[move] != ' ');

        board[move] = 'X';
        printBoard(board);
        delay(1000); // Delay after player's move

        gameOver = checkWinner(board);
        if (gameOver) {
            if (reset(board)) {
                continue;
            } else {
                break;
            }
        }
    }

    printf(WHITE "\n\t\tThanks for playing!\n" DEFAULT);
    return 0;
}

void welcome() {
    system("clear");
    printf(CYAN "\n\t\t𝕎̶𝔼̶𝕃̶ℂ̶𝕆̶𝕄̶𝔼̶ 𝕋̶𝕆̶ 𝕋̶𝕚̶𝕔̶ 𝕋̶𝕒̶𝕔̶ 𝕋̶𝕠̶𝕖̶ 𝔾̶𝕒̶𝕞̶𝕖̶\n\n" DEFAULT);

    printf(YELLOW "\t\t _______________________ \n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   1   |   2   |   3   |\n");
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   4   |   5   |   6   |\n");
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   7   |   8   |   9   |\n");
    printf("\t\t|_______|_______|_______|\n" DEFAULT);
}

void printBoard(char *board) {
    printf(YELLOW "\t\t _______________________ \n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n", board[0], board[1], board[2]);
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n", board[3], board[4], board[5]);
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n", board[6], board[7], board[8]);
    printf("\t\t|_______|_______|_______|\n" DEFAULT);
}

bool checkWinner(char *board) {
    for (int i = 0; i < 3; i++) {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3] != ' ') {
            printf(GREEN "\n\t\t%c wins!\n" DEFAULT, board[i * 3]);
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != ' ') {
            printf(GREEN "\n\t\t%c wins!\n" DEFAULT, board[i]);
            return true;
        }
    }
    if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {
        printf(GREEN "\n\t\t%c wins!\n" DEFAULT, board[0]);
        return true;
    }
    if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {
        printf(GREEN "\n\t\t%c wins!\n" DEFAULT, board[2]);
        return true;
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }

    printf(YELLOW "\n\t\tIt's a draw!\n" DEFAULT);
    return true;
}

bool reset(char *board) {
    char op;
    printf(WHITE "\n\t\tIf you want to play again (y/n): " DEFAULT);
    scanf(" %c", &op);
    op = tolower(op);
    if (op == 'y') {
        for (int i = 0; i < 9; i++) {
            board[i] = ' ';
        }
        return true; // Play again
    }
    return false; // Don't play again
}

void delay(int milliseconds) {
    usleep(milliseconds * 1000);
}
