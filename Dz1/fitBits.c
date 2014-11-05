// Антропов И М Битовые операции. Может ли целое число быть представлено
//                 на машине с n-разрядным словом и дополнительным кодом. Без логических операций.


#include "stdafx.h"
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	long int val, tmp;
	scanf("%ld", &val);
	scanf("%ld", &tmp);
	val = !(val>>(tmp<<3)); 
	printf("%ld", val);
	getch();
	return 0;
}

