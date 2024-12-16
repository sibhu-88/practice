#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void welcome(void);
void print(void);
void check(int *);
void reset();

int player1 = 0, player2 = 0, board[100];

int main()
{
	char ch, num;
	welcome();
	while (1)
	{
		srand(time(NULL));
		while (1)
		{
			printf("#PLAYER1 PRESS ENTER TO TISE ");
			scanf(" %c", &ch);
			num = (rand() % 6) + 1;
			printf("#PLAYER1 TISE is %d \n", num);
			if ((player1 + num) <= 100)
			{
				if (player1 + num != player2)
				{
					player1 += num;
					check(&player1);
					print();
					break;
				}
				else
					printf("Both are same location! Try Agin!\n");
			}
			else {
				printf("Not enagou to move!\n");
				break;
			}
		}
		while (1)
		{
			printf("#PLAYER2 PRESS ENTER TO TISE ");
			scanf(" %c", &ch);
			num = (rand() % 6) + 1;
			printf("#PLAYER2 TISE is %d \n", num);
			if ((player2 + num) <= 100)
			{
				if (player2 + num != player1)
				{
					player2 += num;
					check(&player2);
					print();
					break;
				}
				else
					printf("Both are same location! Try Agin!\n");
			}
			else {
				printf("Not enagou to move!\n");
				break;
			}
		}
	}
}

void welcome(void)
{
	system("clear");
	printf("\n\t\twL2eL2lL2cL2oL2mL2eL2 tL2oL2 SL2nL2aL2kL2eL2 aL2nL2dL2 LL2aL2dL2dL2eL2rL2 GL2aL2mL2eL2\n");
}
void print(void)
{
	int val = 100, i;
	for (i = 0; i < 100; i++)
		board[i] = i + 1;
	for (i = val - 1; i > 0; i--)
	{
		if (i == player1-1 && player1 != 0)
			printf("\033[1;31mP1    \033[0m");
		else if (i == player2-1 && player2 != 0)
			printf("\033[1;34mP2    \033[0m");
		else
		{
			if (board[i] == 100)
				printf("\033[1;30m%d   \033[0m", board[i]);
			else if (board[i] < 10)
				printf("\033[1;30m%d     \033[0m", board[i]);
			else
				printf("\033[1;30m%d    \033[0m", board[i]);
		}

		if (board[i] == 100)
			continue;
		if (board[i] % 10 == 1)
		{
			printf("\n");
			val -= 10;
			for (i -= 10; i < val; i++)
			{
				if (i == player1-1 && player1 != 0)
					printf("\033[1;31mP1    \033[0m");
				else if (i == player2-1 && player2 != 0)
					printf("\033[1;34mP2    \033[0m");
				else
				{
					if (board[i] == 100)
						printf("\033[1;30m%d   \033[0m", board[i]);
					else if (board[i] < 10)
						printf("\033[1;30m%d     \033[0m", board[i]);
					else
						printf("\033[1;30m%d    \033[0m", board[i]);
				}
			}
			val -= 10;
			i = val;
			printf("\n");
		}
	}
}
void check(int *player)
{
	int snakesAndLadders[100] = {[1] = 38, [4] = 10, [9] = 22, [17] = -10, [21] = 21, [28] = 56, [51] = 16, [62] = -43, [64] = -4, [72] = 19, [80] = 19, [87] = -51, [92] = -19, [95] = -20, [98] = -19}, p;

	if (player1 == 100)
	{
		printf("\033[1;36mPLAYER1 WON THE MATCH!\033[0m\n");
		reset();
	}
	else if (player2 == 100)
	{
		printf("\033[1;36mPLAYER2 WON THE MATCH!\033[0m\n");
		reset();
	}
	if (snakesAndLadders[*player] != 0)
	{
		p = *player;
		*player += snakesAndLadders[p];
		if (snakesAndLadders[p] > 0)
			printf("\033[1;35mPlayer UP from %d to %d through ladder\033[0m\n", p, *player);
		else
			printf("\033[1;35mPlayer Down from %d to %d through snake\033[0m\n", p, *player);
	}
}
void reset()
{
	player1 = player2 = 0;
	char op;
	printf("If you want to play again! (Y/N) : ");
	scanf(" %c", &op);
	op = tolower(op);
	if (op == 'y')
		main();
	else
		exit(0);
}