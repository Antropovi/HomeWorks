// LongAlg.c : Антропов Игорь Михайлови Стековый калькулятор
//

#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"

int read_lexem(struct node **lexem)
{
	char temp[2];

	*lexem = NULL;
	
	do
	{
		fgets(temp, 2, stdin);
	}while(temp[0] == ' ' || temp[0] == '\n' || temp[0] == '\r');

	while(temp[0] != ' ' && temp[0] != '\n' && temp[0] != '\r')
	{
		linkedList_Add(temp[0], lexem);
		fgets(temp, 2, stdin);
	}

	return temp[0] != '\n' && temp[0] != '\r';
}

int main()
{
	struct node *lexem;
	struct stack *stack = NULL;
	int flag_read_next;
	int status = 0;

	flag_read_next = read_lexem(&lexem);
	while(lexem != NULL && status == 0)
	{
		if ('0' <= lexem->val && lexem->val <= '9')
			stack = stack_Add(stack, lexem);
		else
			status = stack_Process(&stack, lexem->val) == 0 ? 1 : 0;

		if(flag_read_next)
			flag_read_next = read_lexem(&lexem);
		else
			lexem = NULL;
	}

	if(status == 0)
		stack_Print(stack);

	stack_Free(stack);

	return status;
}

