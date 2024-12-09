#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int userScore = 0, computerScore = 0;
    int userChoice, computerChoice;
    srand(time(0));

    while (1) {
        // Clear the screen and display scores
        system("clear");
        printf("\n\tUser = %d\tComputer = %d\n\n", userScore, computerScore);
        printf("\t1) ROCK\n\t2) PAPER\n\t3) SCISSORS\n");
        printf("\tEnter your choice (1-3): ");
        scanf("%d", &userChoice);

        if (userChoice < 1 || userChoice > 3) {
            printf("\n\tInvalid choice! Please choose 1, 2, or 3.\n");
            usleep(1000000); // Pause for clarity
            continue;
        }

        // Generate computer's choice
        computerChoice = rand() % 3 + 1;

        // Determine the result
        if (userChoice == computerChoice) {
            printf("\n\tDraw! Both chose the same.\n");
        } else if ((userChoice == 1 && computerChoice == 3) || 
                   (userChoice == 2 && computerChoice == 1) || 
                   (userChoice == 3 && computerChoice == 2)) {
            userScore++;
            if (userScore < 3 && computerScore < 3) { // Avoid message if match is ending
                printf("\n\tUser wins this round!\n");
            }
        } else {
            computerScore++;
            if (userScore < 3 && computerScore < 3) { // Avoid message if match is ending
                printf("\n\tComputer wins this round!\n");
            }
        }

        // Check for match winner
        if (userScore == 3) {
            printf("\n\tUser wins the match with a final score of 3!\n");
            break;
        } else if (computerScore == 3) {
            printf("\n\tComputer wins the match with a final score of 3!\n");
            break;
        }

        printf("\n\tPress Enter to continue...");
        getchar(); // Clear the newline left by scanf
        getchar(); // Wait for user input
    }

    return 0;
}
