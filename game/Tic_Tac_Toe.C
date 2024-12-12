#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void welcome(void);
void printBoard(char*);
void checkWinner(char*);
void reset(char *);

int main() {
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int move;

    welcome();

    while (1) {
        // Computer's turn
        srand(time(0));
        int computerMove = rand() % 9;
        while (board[computerMove] != ' ') {
            computerMove = rand() % 9;
        }
        board[computerMove] = 'O';
        printf("\n\t\tcomputer Move\n");
        printBoard(board);
        checkWinner(board);

        // Player's turn
        do {
            printf("\n\t\tEnter Your move (1-9): ");
            scanf("%d", &move);
            move--; // Adjust for 0-indexed array
            if (board[move] != ' ') {
                printf("\n\t\tAlready occupied! Try again.\n");
            }
        } while (board[move] != ' ');
        board[move] = 'X';
        printBoard(board);
        checkWinner(board);
    }

    return 0;
}

void welcome() {
    system("clear");
    printf("\n\t\t𝕎̶𝔼̶𝕃̶ℂ̶𝕆̶𝕄̶𝔼̶ 𝕋̶𝕆̶ 𝕋̶𝕚̶𝕔̶ 𝕋̶𝕒̶𝕔̶ 𝕋̶𝕠̶𝕖̶ 𝔾̶𝕒̶𝕞̶𝕖̶\n");

    printf("\n\t\t _______________________ \n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   1   |   2   |   3   |\n");
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   4   |   5   |   6   |\n");
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   7   |   8   |   9   |\n");
    printf("\t\t|_______|_______|_______|\n");
}

void printBoard(char *board) {
    printf("\t\t _______________________ \n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n",board[0],board[1],board[2]);
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n",board[3],board[4],board[5]);
    printf("\t\t|_______|_______|_______|\n");
    printf("\t\t|       |       |       |\n");
    printf("\t\t|   %c   |   %c   |   %c   |\n",board[6],board[7],board[8]);
    printf("\t\t|_______|_______|_______|\n");
}

void checkWinner(char *board) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3] != ' ') {
            printf("\n\t\t%c wins!\n", board[i * 3]);
            reset(board);
            exit(0);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != ' ') {
            printf("\n\t\t%c wins!\n", board[i]);
            reset(board);
            exit(0);
        }
    }
    if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {
        printf("\n\t\t%c wins!\n", board[0]);
        reset(board);
        exit(0);
    }
    if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {
        printf("\n\t\t%c wins!\n", board[2]);
        reset(board);
        exit(0);
    }

    // Check for a draw
    int i;
    for (i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            break;
        }
    }
    if (i == 9) {
        printf("\n\t\tIt's a draw!\n");
        reset(board);
        exit(0);
    }
}

void reset(char *board) {
    char op;
    printf("\n\t\tIf you want to play again (y/n): ");
    scanf(" %c", &op);
    op = tolower(op);
    if (op == 'y') {
        for (int i = 0; i < 9; i++) {
            board[i] = ' ';
        }
        main();
    }
}