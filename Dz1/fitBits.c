// Антропов И М Битовые операции. Может ли целое число быть представлено
//                 на машине с n-разрядным словом и дополнительным кодом. Без логических операций.


#include "stdafx.h"

int main()
{
	long int val = 0 , tmp = 0;
	scanf("%ld",  &val);
	scanf("%ld",  &tmp);

	int absval = (val ^ (val >> 31)) - (val>>31); //val=abs(val)
	int result = !(absval >> (tmp << 3)); 
	printf("%ld",  result);

	return 0;
}

