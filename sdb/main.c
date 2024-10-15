#include "header.h"


void menu1(){

	printf("\n\t****STUDENT RECORD MENU****\n\n");
	printf("\t  a/A : Add New Record\n");
	printf("\t  d/D : Delete A Record\n");
	printf("\t  s/S : Show The List\n");
	printf("\t  m/M : Modify A Record\n");
	printf("\t  v/V : Save\n");
	printf("\t  e/E : Exit\n");
	printf("\t  t/T : Sort The List\n");
	printf("\t  l/L : Delete All The Records\n");
	printf("\t  r/R : Reverse The List\n\n");
	printf("\t  Enter Your Choice : ");
}

void menu2(){
	printf("\t  R/r : Enter Roll To Delete\n");
        printf("\t  N/n : Enter Name To Delete\n");
	printf("\t  Enter : ");
}

void menu3(){
	printf("\t  Enter Which Record To Search Fo Nodification\n");
	printf("\t  R/r : To Search A RollNo\n");
        printf("\t  N/n : To Search A Name\n");
	printf("\t  P/P : To Search A percentage\n");
        printf("\t  Enter : ");
}

void menu4(){
	printf("\t  S/s : Save And Exit\n");
        printf("\t  E/e : Exit Without Saving\n");
        printf("\t  Enter : ");
}

void menu5(){
        printf("\t  N/n : Sort With Name\n");
	printf("\t  P/p : Sort With Percentage\n");
	printf("\t  Enter : ");
}

int main(){
	char op;
	SDB *hptr=0;
	while(1){
		menu1();
		scanf(" %c",&op);

		op= tolower(op);
		switch(op){
			case 'a': Add_new_record(&hptr); break;
			case 'd': Delete_record(&hptr); break;
			case 's': Show_list(hptr); break;
			case 'm': Modify_record(&hptr); break;
			case 'v': Save_record(hptr); break;
			case 'e': printf("Exit From the Student DataBase\n"); return 0;
			case 't': Sort_list(hptr); break;
			case 'l': Delete_all_record(&hptr); break;
			case 'r': Reverse_list(&hptr); break;
			default : printf("Invalid option.");
		}
	}
}
