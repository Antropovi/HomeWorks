
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


void numbers_Read(struct number *num, struct node *lexem)
{
	int val;
	int counter=0;
	int pow;
	struct node *symbol;
	
	symbol = lexem;
	while (symbol != NULL){
		val = 0;
		pow = 1;
		for (counter=0; counet < 3 && symbol != NULL; counter++){
			if (symbol->val == '-') {
				num->sign = -1;
				symbol = symbol->next;
				break;
			}
			else if (symbol->val == '+')
			{
				symbol = symbol->next;
				break;
			}
			val += pow*(symbol->val - '0');
			pow *= 10;
			symbol = symbol->next;
		}
		linkedList_Add(val, &(num->head));
	}

	linkedList_Revert(&(num->head));

	linkedList_Free(lexem);
}

void numbers_Free(struct number* num)
{
	linkedList_Free(num->head);
	free(num);
}
