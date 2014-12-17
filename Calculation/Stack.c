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

void stack_Revert(struct stack ** head){
 struct stack * prev = NULL;
 struct stack * next = NULL;
 struct stack * curr = *head;

 while (curr) {
  next = curr->next;
  curr->next = prev;
  prev = curr;
  curr = next;
 }

 *head = prev;
}

// анализ далеко не полный
struct stack *stack_Add(struct stack *stack, struct node *lexem){

	struct stack *item = (struct stack *)malloc(sizeof(struct stack));
	item->next = stack;
	// если 1 символ и не число, то оператор
	if(lexem->next==NULL && !('0'<=lexem->val && lexem->val<='9') )
	{
		item->operation = lexem->val;
		item->number = NULL;
		linkedList_Free(lexem);
	}
	// если начались с цифры, то число (лексема ведь перевернута)
	else if ('0'<=lexem->val && lexem->val<='9')
	{
		item->operation = 'n';
		item->number = numbers_Init();
		numbers_Read(item->number, lexem);
	}
	// иначе что то непонятное
	else
	{
		item->operation = 'e';
		item->number = NULL;
		linkedList_Free(lexem);
	}

	return item;
}


int stack_Process(struct stack **stack)
{
	struct number *finaly;
	int result = 1;	//true

	// пока вверху стека тройка "число-число-операция"
	// выполняем операцию и заменяем на число-результат
	while((*stack)!=NULL && 
		(*stack)->next!=NULL && 
		(*stack)->next->next!=NULL &&
		(*stack)->operation=='n' && 
		(*stack)->next->operation=='n' && 
		(*stack)->next->next->operation!='n')
	{
		switch ((*stack)->next->next->operation)
		{
		case '+':
			finaly = LongMath_plus((*stack)->next->number, (*stack)->number);
			break;
		case '-':
			finaly = LongMath_minus((*stack)->next->number, (*stack)->number);
			break;
		case '*':
			finaly = LongMath_multi((*stack)->next->number, (*stack)->number);
			break;
		case '/':
			finaly = LongMath_div((*stack)->next->number, (*stack)->number);
			break;
		default:	// unknown operator
			printf("unknown operator\n");
			finaly = NULL;
		}

		if (finaly != NULL){ 
			*stack = stack_FreeTop(*stack);	// remove operator
			*stack = stack_FreeTop(*stack);	// remove first operand
			*stack = stack_FreeTop(*stack);	// remove second operand

			*stack = stack_AddNumber(*stack, finaly); // add result
		}
		else	// иначе прекращаем обработку
		{
			result = 0; //false
			break;
		}
	} 
	return result;
}

void stack_Print(struct stack *stack)
{
	stack_Revert(&stack);

	while (stack != NULL){
		if (stack->operation=='n')
		{
			if (stack->number->sign!=1) printf("-");
		  linkedList_Print(&(stack->number->head));
		}
		else
			printf("%c ", stack->operation);
		//printf(" ");

		stack = stack->next;
	}

	printf("\n");
}

void stack_Free(struct stack *stack)
{
	while(stack!=NULL){
		stack = stack_FreeTop(stack);
	}
}
