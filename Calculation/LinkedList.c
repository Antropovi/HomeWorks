#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"


void linkedList_Revert(struct node ** head){
 	struct node * prev = NULL;
 	struct node * next = NULL;
 	struct node * curr = *head;

	 while (curr) 
	 {
  	 	next = curr->next;
 		curr->next = prev;
 		prev = curr;
 		curr = next;
	 }

 	*head = prev;
}


void linkedList_Add(int val, struct node ** head)
{
	struct node * new_node = (struct node*)malloc(sizeof(struct node));
	new_node->next = *head;
	*head = new_node;
	new_node->val=val;
}

void linkedList_Insert(struct node ** head)
{
	struct node * new_node = (struct node*)malloc(sizeof(struct node));
	new_node->next = NULL;
	*head = new_node;
	new_node->val = 0;
}

void linkedList_Print(struct node ** head)
{

	struct node * curr;
	struct node * temp;

	linkedList_Revert(head);
	while ((*head)->val == 0 && (*head)->next != NULL) 
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}

	printf("%d", (*head)->val);
	curr = (*head)->next;
	while (curr) 
	{
		printf("%03d" , curr->val);
		curr = curr->next;
	}
}

void linkedList_Free(struct node *head)
{
	struct node* next;
	struct node* n = head;
	while(n != NULL)
	{
		next = n->next;
		free(n);
		n = next;
	}
}

