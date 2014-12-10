// LongAlg.cpp : Defines the entry point for the console application.
//

#include <conio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <string.h>

struct stack *stack_AddNumber(struct stack *stack, struct number *number){

	struct stack *item = (struct stack *)malloc(sizeof(struct stack));
	item->next = stack;
	item->operation = 'n';
	item->number = number;
	return item;
}

struct stack *stack_FreeTop(struct stack *stack)
{
	struct stack *item;

	if(stack!=NULL){
		if(stack->operation=='n')
		{
			numbers_Free(stack->number);
		}
		item = stack->next;
		free(stack);
		
		stack = item;
	}
	return stack;
}

struct stack *stack_Add(struct stack *stack, char *string){

	struct stack *item = (struct stack *)malloc(sizeof(struct stack));
	item->next = stack;
	if(string[1]==0 && 
		(string[0]=='+' || string[0]=='-' || string[0]=='*' || string[0]=='/'))
	{
		item->operation = string[0];
		item->number = NULL;
	}
	else
	{
		item->operation = 'n';
		item->number = numbers_Init();
		numbers_Read(item->number, string);
	}
	return item;
}


struct stack *stack_Process(struct stack *stack)
{
	struct number *finaly;

	// пока вверху стека тройка "операция-число-число)
	// выполняем операцию и заменяем на число-результат
	while(stack!=NULL && stack->next!=NULL && stack->next->next!=NULL &&
		stack->operation!='n' &&
		stack->next->operation=='n' && stack->next->next->operation=='n')
	{
		switch (stack->operation)
		{
		case '+':
			finaly = LongMath_plus(stack->next->number, stack->next->next->number);
			break;
		case '-':
			finaly = LongMath_minus(stack->next->number, stack->next->next->number);
			break;
		case '*':
			finaly = LongMath_multi(stack->next->number, stack->next->next->number);
			break;
		case '/':
			finaly = LongMath_div(stack->next->number, stack->next->next->number);
			break;
		default:	// unknown operator
			printf("unknown operator\n");
			finaly = numbers_Init();
		}

		stack = stack_FreeTop(stack);	// remove operator
		stack = stack_FreeTop(stack);	// remove first operand
		stack = stack_FreeTop(stack);	// remove second operand

		stack = stack_AddNumber(stack, finaly); // add result
	}
	return stack;
}

void stack_Print(struct stack *stack)
{
	while(stack!=NULL){
		if(stack->operation=='n')
		{
			if (stack->number->sign!=1) printf("-");
		  linkedList_Print(stack->number->head);
		}
		else
			printf("%c", stack->operation);
		printf(" ");

		stack = stack->next;
	}
}

void stack_Free(struct stack *stack)
{
	while(stack!=NULL){
		stack = stack_FreeTop(stack);
	}
}
