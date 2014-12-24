
#include <stdlib.h>
#include "stdafx.h"
#include <string.h>

struct stack *stack_AddNumber(struct stack *stack, struct number *number)
{
	struct stack *item = (struct stack *)malloc(sizeof(struct stack));
	item->next = stack;
	item->operation = 'n';
	item->number = number;
	return item;
}

struct stack *stack_FreeTop(struct stack *stack)
{
	struct stack *item;

	if(stack != NULL){
		if(stack->operation == 'n')
		{
			numbers_Free(stack->number);
		}
		item = stack->next;
		free(stack);
		
		stack = item;
	}
	return stack;
}

void stack_Revert(struct stack ** head)
{
	struct stack * prev = NULL;
	struct stack * next = NULL;
	struct stack * curr = *head;

	while (curr) 
	{
 		next = curr->next;
 		curr->next = prev;
		prev = curr;
  		curr = next;
 	}

 	*head = prev;
}


struct stack *stack_Add(struct stack *stack, struct node *lexem)
{
	struct stack *item = (struct stack *)malloc(sizeof(struct stack));
	item->next = stack;
	
	if(lexem->next == NULL && !('0' <= lexem->val && lexem->val <= '9') )
	{
		item->operation = lexem->val;
		item->number = NULL;
		linkedList_Free(lexem);
	}
	else if ('0' <= lexem->val && lexem->val <= '9')
	{
		item->operation = 'n';
		item->number = numbers_Init();
		numbers_Read(item->number, lexem);
	}
	else
	{
		item->operation = 'e';
		item->number = NULL;
		linkedList_Free(lexem);
	}

	return item;
}


int stack_Process(struct stack **stack, char operation)
{
	struct number *finaly;
	int result = 1;	

	if(*stack == NULL || ((*stack)->next == NULL && operation != '=') )
	{
		printf("Not enough arguments\n");
		result = 0;
	}
	else
	{
		switch (operation)
		{
		case '+':
			finaly = longMath_Plus((*stack)->number, (*stack)->next->number);
			break;
		case '-':
			finaly = longMath_Minus((*stack)->number, (*stack)->next->number);
			break;
		case '*':
			finaly = longMath_Multi((*stack)->number, (*stack)->next->number);
			break;
		case '/':
			finaly = longMath_Div((*stack)->number, (*stack)->next->number);
			break;
		case '=':
			printf("[");
			if ((*stack)->number->sign!=1) printf("-");
			linkedList_Print(&((*stack)->number->head));
			printf("]\n");
			finaly = NULL;
			break;
		default:	
			printf("Unknown command\n");
			finaly = NULL;
			result = 0;
		}

		if (finaly != NULL){ 
			*stack = stack_FreeTop(*stack);	
			*stack = stack_FreeTop(*stack);	

			*stack = stack_AddNumber(*stack, finaly); 
		}
		else if(operation!='=')	
		{
			result = 0; 
		}
	}
	return result;
}

void stack_Print(struct stack *stack)
{
	int first = 1;

	printf("[");

	while (stack != NULL)
	{
		
		if(!first)
			printf("; ");

		if (stack->operation == 'n')
		{
			if (stack->number->sign != 1) printf("-");
			linkedList_Print(&(stack->number->head));
		}
		else
		{
			printf("%c", stack->operation);
		}

		stack = stack->next;
		first = 0;
	}

	printf("]\n");
}

void stack_Free(struct stack *stack)
{
	while(stack!=NULL)
	{
		stack = stack_FreeTop(stack);
	}
}
