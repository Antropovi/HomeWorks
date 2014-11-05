// Антропов И М Битовые операции. Может ли целое число быть представлено
//                 на машине с n-разрядным словом и дополнительным кодом. Без логических операций.


#include "stdafx.h"
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	long int val, tmp;
	scanf("%ld", &val);
	scanf("%ld", &tmp);
	int ABSval = (val^(val>>31)) - (val>>31); //val=abs(val)
	int result = !(ABSval>>(tmp<<3)); 
	printf("%ld", result);
	getch();
	return 0;
}

