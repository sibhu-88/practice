#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_TRIES 7

int main() {
	int tries=0,num,g_rand;
	system("clear");
	printf("\n\t\tWelcome to Number Guessing Game\n");
	printf("\n\t\tSelect a Number Between 1 to 100\n");
	srand(time(0));
	g_rand = rand()%100;

	while (tries<MAX_TRIES)
	{
		printf("\t\tYou have %d Tries left\n",MAX_TRIES-tries);
		printf("\t\tEnter Your Guess : ");
		scanf("%d",&num);
		if (g_rand==num)
		{
			printf("\n\t\tYour Guessing is currect\n\t\tYou guesses %d tries Weldone\n",tries);
			exit(0);
		}
		else {
			if (num<g_rand)
				printf("\t\tToo Low! Try againe!\n\n");
			else
				printf("\t\tToo High! Try againe!\n\n");
			tries++;
		}
	}
	printf("\t\tYour Tries is over! you Lose!\n");
}