#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"


struct number* numbers_Init()
{
	struct number* new_number = (struct number*)malloc(sizeof(struct number));
	new_number->sign = 1;
	new_number->head = NULL;
	return new_number;
}


void numbers_Read(struct number *num)
{
	char temp[2];

	do
	{
		fgets(temp, 2, stdin);
	} while(temp[0] == ' ' || temp[0] == '\n' || temp[0] == '\r');

	while(temp[0] != ' ' && temp[0] != '\n' && temp[0] != '\r')
	{
		linkedList_Add(temp[0], &(num->head));
		fgets(temp, 2, stdin);
	}

	linkedList_Revert(&(num->head));
}

void numbers_Free(struct number* num)
{
	struct node* next;
	struct node* n = num->head;
	while(n != NULL)
	{
		next = n->next;
		free(n);
		n = next;
	}
  	free(num);
}
