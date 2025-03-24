#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

void dicess_1(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_2(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0           |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|           0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_3(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0           |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|           0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_4(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_5(void){
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|       0       |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

void dicess_6(void){
	printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t|   0       0   |\n");
        printf("\t\t\t\t\t\t|               |\n");
        printf("\t\t\t\t\t\t+---------------+\n");
        printf("\n\n\n\n\n\n\n\n");
}

int main(){
	int i,j,ran;
	char op;
	void (*fdicess[])(void) = {dicess_1, dicess_2, dicess_3, dicess_4, dicess_5, dicess_6};
	do{
		printf("Type S to start Dicess : ");
		scanf(" %c",&op);
		op=tolower(op);
		if(op!='s') break;
		srand(time(0));
		ran=rand() % 6;

		for(j=0;j<10;j++){
		     for(i=0;i<6;i++){
			system("clear");
        			fdicess[i]();
			usleep(50000);
		     }
		}
		system("clear");
		fdicess[ran]();
		printf("You got %d \n",ran+1);
		printf("Do you want to Dice again (Y/N): ");
                scanf(" %c",&op);
                op=tolower(op);
	}while(op=='y');
}

