#include "header.h"

void Add_new_record(SDB **ptr){

	SDB *temp= (SDB *)malloc(sizeof(SDB));

	printf("\tEnter Your Name : ");
	scanf(" %[^\n]",temp->name);
	printf("\tEnter Your Percentage : ");
	scanf("%d",&temp->percentage);

	if(*ptr==0){
		*ptr = temp;
		temp->next=0;
		temp->rollno =1;
	}else{

		SDB *last=*ptr;
		while(last->next!=0) last = last->next;

		temp->rollno = (last->rollno + 1);
		temp->next = last->next;
		last->next = temp;
	}

}
