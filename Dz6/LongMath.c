#include <conio.h>
#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"

int longMath_CompareWithoutSign(struct node *node1, struct node *node2)
{
	int result = 0;
	struct node *n1 = node1;
	struct node *n2 = node2;

	while(n1 != NULL || n2 != NULL){
		if(n2 == NULL && n1 != NULL && n1->val!=0)
		{
			return 1;
		}
		if(n1 == NULL && n2 != NULL && n2->val != 0)
		{
			return -1;
		}
		if(n1 != NULL && n2 != NULL && n1->val != n2->val)
		{
			result = n1->val - n2->val;
		}
		if(n1 != NULL)
		{
			n1 = n1->next;
		}
		if(n2 != NULL)
		{
			n2 = n2->next;
		}
	}

	return result > 0 ? 1 : (result < 0 ? -1 : 0);

}

void longMath_PlusWithoutSign(struct node *node1, struct node *node2, struct node **result)
{
	struct node *n1 = node1;
	struct node *n2 = node2;
	int sum = 0;
	

	while(n1 != NULL || n2 != NULL){
		if(n1 != NULL)
		{
			sum += n1->val;
			n1 = n1->next;
		}
		if(n2 != NULL)
		{
			sum += n2->val;
			n2 = n2->next;
		}

		linkedList_Add(sum % 1000, result);

		sum /= 1000;
	}

	if(sum != 0)
	{
		linkedList_Add(sum, result);
	}
}

void longMath_MinusWithoutSign(struct node *node1, struct node *node2, struct node **result)
{
	struct node *n1 = node1;
	struct node *n2 = node2;
	int div = 0;
	int rev = 0;
	

	while(n1 != NULL || n2 != NULL)
	{
		if(n1 != NULL)
		{
			div = n1->val;
			n1 = n1->next;
		}
		if(n2 != NULL)
		{
			div -= n2->val;
			n2 = n2->next;
		}

		div -= rev;

		if(div < 0)
		{
			rev = -1;
			div += 1000;
		}
		else
		{
			rev = 0;
		}
		linkedList_Add(div, result);
	}
}

void longMath_Add(struct node **node, int value)
{
	if(*node == NULL)
	{
		linkedList_Add(0, node);
	}

	if(value == 0)
	{
		return;
	}

	value += (*node)->val;
	(*node)->val = value %1000;

	longMath_Add(&(*node)->next, value / 1000);
}

struct number *longMath_Plus(struct number *num1, struct number *num2)
{
	struct number* result;
	
	result = numbers_Init();

	if(num1->sign == num2->sign)
	{
		result->sign = num1->sign;
		longMath_PlusWithoutSign(num1->head, num2->head, &(result->head));
	}
	else
	{
		if(longMath_CompareWithoutSign(num1->head, num2->head) >0)
		{
			result->sign = num1->sign;
			longMath_MinusWithoutSign(num1->head, num2->head, &(result->head));
		}
		else
		{
			result->sign = num2->sign;
			longMath_MinusWithoutSign(num2->head, num1->head, &(result->head));
		}
	}

	linkedList_Revert(&(result->head));

	return result;
}


struct number *longMath_Minus(struct number *num1, struct number *num2)
{
	struct number* result;
	
	result = numbers_Init();

	if(num1->sign == num2->sign)
	{
		if(longMath_CompareWithoutSign(num1->head, num2->head) >0)
		{
			result->sign = num1->sign;
			longMath_MinusWithoutSign(num1->head, num2->head, &(result->head));
		}
		else
		{
			result->sign = num1->sign == 1 ? -1 : 1;
			longMath_MinusWithoutSign(num2->head, num1->head, &(result->head));
		}
	}
	else
	{
		if(longMath_CompareWithoutSign(num1->head, num2->head) >0)
		{
			result->sign = num1->sign;
			longMath_PlusWithoutSign(num1->head, num2->head, &(result->head));
		}
		else
		{
			result->sign = num1->sign;
			longMath_PlusWithoutSign(num2->head, num1->head, &(result->head));
		}
	}

	linkedList_Revert(&(result->head));

	return result;
}
void longMath_MulInt(struct node **node, int value)
{
	struct node *n = *node;
	int add_value = 0;
	
	while(n != NULL)
	{
		n->val = n->val * value + add_value;
		add_value = n->val / 1000;
		n->val = n->val % 1000;
		n = n->next;
	}

	while(add_value != 0)
	{
		n = *node;
		while(n->next!=NULL)
		{
			n = n->next;
		}
		linkedList_Insert(&(n->next));
		n->next->val = add_value % 1000;
		add_value /= 1000;
	}
}

void longMath_DivInt(struct node **node, int value)
{
	struct node *n;
	int add_value = 0;
	int div;

	linkedList_Revert(node);
	n = *node;
		
	while(n != NULL)
	{
		div = (n->val + 1000 * add_value) / value;
		add_value = n->val - div * value;
		n->val = div;

		n = n->next;
	}

	linkedList_Revert(node);
}


struct number *longMath_Multi(struct number *num1, struct number *num2)
{
	struct number* result;
	struct node *n1;
	struct node *n2;
	struct node **n_res;
	struct node **n_res2;
	
	result = numbers_Init();
	result->sign = num1->sign==num2->sign ? 1 : -1;

	n1 = num1->head;
	n_res = &(result->head);
	while(n1!=NULL)
	{
		n2 = num2->head;
		n_res2 = n_res;
		while(n2!=NULL)
		{
			longMath_Add(n_res2, n1->val * n2->val);
			n_res2 = &((*n_res2)->next);
			n2=n2->next;
		}
		n_res = &((*n_res)->next);
		n1 = n1->next;
	}


	return result;
}

struct number *longMath_Div(struct number *num1, struct number *num2)
{
	struct number* result;
	
	int pow = 0;
	int i;
	struct node *n1;
	struct node *n2;
	int tmp;
	
	result = numbers_Init();
	result->sign = num1->sign==num2->sign ? 1 : -1;

	while(longMath_CompareWithoutSign(num1->head, num2->head)>=0)
	{
		longMath_MulInt(&(num2->head), 10);
		pow++;
	}

	pow--;

	for(i=0; i <= pow; i++){

		longMath_MulInt(&(result->head), 10);
		longMath_DivInt(&(num2->head), 10);
		while(longMath_CompareWithoutSign(num1->head, num2->head)>=0)
		{
			longMath_Add(&(result->head), 1);

			n1 = num1->head;
			n2 = num2->head;
			tmp = 0;

			while(n1 != NULL && n2 != NULL)
			{
				n1->val -= n2->val + tmp;
				tmp = 0;
				while(n1->val <0)
				{
					n1->val += 1000;
					tmp++;
				}

				n1 = n1->next;
				n2 = n2->next;
			}
			while(tmp > 0 && n1 != NULL)
			{
				n1->val -= tmp;
				tmp = 0;
				while(n1->val <0)
				{
					n1->val += 1000;
					tmp++;
				}
				n1 = n1->next;
			}
		}
	}
	return result;
}
