// LongAlg.c: Антропов Игорь Михайлович Длинная арифметика с 2 операндами
//

#include "stdafx.h"
#include <string.h>


int main()
{
	struct number *first = numbers_Init();
	struct number *second = numbers_Init();
	struct number *finaly;
	char operation[2];

	numbers_Read(first);
	fgets(operation, 2, stdin);
	numbers_Read(second);
	switch (operation[0])
	{
	case '+':
		finaly = longMath_Plus(first, second);
		break;
	case '-':
		finaly = longMath_Minus(first, second);
		break;
	case '*':
		finaly = longMath_Multi(first, second);
		break;
	case '/':
		finaly = longMath_Div(first, second);
		break;
	}

	if (finaly->sign != 1) printf("-");
	linkedList_Print(finaly->head);
	numbers_Free(first);
	numbers_Free(second);
	numbers_Free(finaly);
	return 0;
}

