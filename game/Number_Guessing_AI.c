#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h> // For abs()

// ANSI color codes (same as before)
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define DEFAULT "\033[0m"

#define MAX_TRIES 7

void delay(int milliseconds);

int main() {
    int tries = 0, num, g_rand;

    system("clear");
    printf(CYAN "\n\t\tWelcome to Number Guessing Game\n" DEFAULT);
    printf(YELLOW "\n\t\tGuess a Number Between 1 to 100\n" DEFAULT);

    srand(time(0));
    g_rand = (rand() % 100) + 1;

    while (tries < MAX_TRIES) {
        printf(WHITE "\n\t\tYou have %d Tries left\n" DEFAULT, MAX_TRIES - tries);
        printf(BLUE "\t\tEnter Your Guess : " DEFAULT);

        if (scanf("%d", &num) != 1) {
            printf(RED "\t\tInvalid input. Please enter a number.\n\n" DEFAULT);
            while (getchar() != '\n');
            delay(1500);
            system("clear");
            printf(CYAN "\n\t\tWelcome to Number Guessing Game\n" DEFAULT);
            printf(YELLOW "\n\t\tGuess a Number Between 1 to 100\n" DEFAULT);
            continue;
        }

        if (num < 1 || num > 100) {
            printf(RED "\t\tNumber is out of range. Please enter between 1 to 100\n\n" DEFAULT);
            delay(1500);
            system("clear");
            printf(CYAN "\n\t\tWelcome to Number Guessing Game\n" DEFAULT);
            printf(YELLOW "\n\t\tGuess a Number Between 1 to 100\n" DEFAULT);
            continue;
        }

        if (g_rand == num) {
            printf(GREEN "\n\t\tYour Guess is correct!\n\t\tYou guessed in %d tries. Well done!\n" DEFAULT, tries + 1);
            break;
        } else {
            int diff = abs(g_rand - num);
            if (diff <= 10) {
                printf(YELLOW "\t\tYou are close! (%d)\n" DEFAULT, num);
                if (num < g_rand) {
                    printf(MAGENTA "\t\tToo Low!\n\n" DEFAULT);
                } else {
                    printf(MAGENTA "\t\tToo High!\n\n" DEFAULT);
                }
            } else {
                if (num < g_rand) {
                    printf(MAGENTA "\t\tToo Low! Try again!\n\n" DEFAULT);
                } else {
                    printf(MAGENTA "\t\tToo High! Try again!\n\n" DEFAULT);
                }
            }
            tries++;
            delay(1000);
            system("clear");
            printf(CYAN "\n\t\tWelcome to Number Guessing Game\n" DEFAULT);
            printf(YELLOW "\n\t\tGuess a Number Between 1 to 100\n" DEFAULT);
        }
    }

    if (tries == MAX_TRIES) {
        printf(RED "\t\tYour Tries are over! You Lose!\n" DEFAULT);
        printf(YELLOW "\t\tThe correct number was: %d\n" DEFAULT, g_rand);
    }

    return 0;
}

void delay(int milliseconds) {
    usleep(milliseconds * 1000);
}