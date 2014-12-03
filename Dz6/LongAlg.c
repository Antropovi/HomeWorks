// LongAlg.cpp : Defines the entry point for the console application.
//

#include <conio.h>
#include "stdafx.h"
#include <string.h>


int main()
{
	char InPutString[256];
	char operation;
	struct number *first = numbers_Init();
	struct number *second = numbers_Init();
	struct number *finaly;

	scanf("%s", InPutString);
	numbers_Read(first, InPutString);
	scanf("%s", InPutString);
	operation = InPutString[0];
	scanf("%s", InPutString);
	numbers_Read(second, InPutString);
	switch (operation)
	{
	case '+':
		finaly = LongMath_plus(first, second);
		break;
	case '-':
		finaly = LongMath_minus(first, second);
		break;
	case '*':
		finaly = LongMath_multi(first, second);
		break;
	case '/':
		finaly = LongMath_div(first, second);
		break;
	}
	if (finaly->sign!=1) printf("-");
	linkedList_Print(finaly->head);
	numbers_Free(first);
	numbers_Free(second);
	numbers_Free(finaly);
	getch();
	return 0;
}

