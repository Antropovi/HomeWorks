#include <conio.h>
#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"


struct number* numbers_Init(){
	struct number* new_number = (struct number*)malloc(sizeof(struct number));
	new_number->sign = 1;
	new_number->head = NULL;
	return new_number;
}


void numbers_Read(struct number *num, char *string){
	int val;
	int i=0;
	if (string[0]=='-') {
		num->sign=-1;
		string[0]='0';
	}
	else if (string[0]=='+')
	{
		string[0]='0';
	}
	for (i=strlen(string)-1; i>=0; i=i-3)
	{
		val = string[i]-'0' +10* (i-1>=0 ? (string[i-1]-'0') : 0)+100* (i-2>=0 ? (string[i-2]-'0') : 0);
		linkedList_Add(val, &(num->head));
	}
	linkedList_Revert(&(num->head));
}

void numbers_Free(struct number* num){
	 struct node* next;
	struct node* n = num->head;
	while(n!=NULL){
	next = n->next;
	free(n);
	n=next;
	}
  free(num);
}