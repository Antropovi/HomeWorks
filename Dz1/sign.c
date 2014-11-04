// HomeWork8.cpp : Битовые операции. Знак целого числа (-1, 0, 1). Без логических операций.
//

#include "stdafx.h"
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int val;
	scanf("%d",&val);
	printf("%d\n", (val >>(sizeof(int) << 3 - 1) ) | (!!val));
	getch();
	return 0;
}

