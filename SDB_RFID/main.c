#include "header.h"

int main(){
	
	char ch;
	system("clear");
	printf("\t\t\tStudents Data Base\n\n");
	printf("\t\t S/s Search the record\n");
	printf("\t\t A/a Add the record\n\n");
	printf("Enter the option: ");
	scanf(" %c",&ch);

	ch=tolower(ch);
	switch(ch){
		case 's':printf("Scanning the Id.......\n"); break;
		case 'a':printf("Adding the data.\n"); break;
		default:
			printf("invalid option"); break; 
	}

	
}
