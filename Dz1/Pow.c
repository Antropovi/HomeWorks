// HomeWork1.cpp : Реализация "быстрого" возведения числа в степень
// Антропов И 171г 31.10.2013

#include "stdafx.h"
#include <conio.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int a=0,n=0,s=1;
	scanf("%d\n", &a);
	scanf("%d", &n);
	while (n)
		{
		if (!(n&1))
			{
			n=n>>1;
			a*=a;
			}
		else
			{
			n--;
			s*=a;
			}
		}
	printf("%d",s);

    getch();
	return 0;
}

