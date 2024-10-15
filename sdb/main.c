#include "header.h"

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
