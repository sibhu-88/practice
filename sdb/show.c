#include "header.h"

void Show_list(SDB *ptr){
	printf("\n\tShowing  list :\n");
	printf("\tRoll.No\t\tName\t\tpercentage\n");
	while(ptr!=0){
		printf("\t%d\t\t%s\t\t%d\n",(ptr)->rollno,(ptr)->name,(ptr)->percentage);
		ptr=ptr->next;
	}
}

void Sort_list(SDB *ptr){
	printf("Sort list\n");

}

void Reverse_list(SDB **ptr){
	printf("reverse list\n");

}
