// Реализация односвязного списка
// Антропов ИМ 12.11.2014


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


struct node
{
	float val;
	node * next;
};




void Add(float val, node **head)
{
	node * new_node = (node*)malloc(sizeof(node));
	new_node->next = *head;
	*head = new_node;
	new_node->val=val;
}

void Print(node **head)
{
	node *curr = *head;
	while (curr) 
	{
		printf("%.2f  " ,curr->val);
		curr = curr->next;
	}
	printf("\n");
}
 
void Remove(float ReVal, node **head)
{

	node *tmp = NULL;
	node *curr = NULL;

	if (*head != NULL)
	{
		if((*head)->val == ReVal)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
		else
		{
			curr = *head;
			while (curr->next)
			{
				if (curr->next->val == ReVal) 
				{ 
					tmp = curr->next;
					curr->next = curr->next->next;
					free(tmp);
					break;
				}
			curr = curr->next;  
			}
		}
	}
}


int main()
{
	char String[100] = "";
	float f = 0;
	node *head = NULL;
	printf("Введите Строку где, a ARG - добавить число\n");
	printf("r ARG - удалить первое вхождение числа\n");
	printf("p - вывести весь список\nq - выход из программы\n");

	scanf("%s", String);

	while(String[0]!='q')
	{
		switch (String[0])
		{
			case 'p' : 
			{
				Print(&head);
				break;
			}
			case 'a' : 
			{
				scanf("%f", &f);
				Add(f, &head);
				break;
			}
			case 'r' :
			{
				scanf("%f", &f);
				Remove(f, &head);
				break;
			}
		}

		scanf("%s", String);
	}

	return 0;
}
