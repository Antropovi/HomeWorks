// HomeWork8.cpp : Sign of nuber. 
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

