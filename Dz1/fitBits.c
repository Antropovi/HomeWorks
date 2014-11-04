// HomeWork7.cpp : Ѕитовые операции. ћожет ли целое число быть представлено
//                 на машине с n-разр€дным словом и дополнительным кодом. Ѕез логических операций.


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

