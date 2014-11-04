// HomeWork5.cpp : Вывод внутрености float 1 способ
//

#include "stdafx.h"
#include <conio.h>

struct MyStruct
{
	long unsigned ival;
	float fval;
};

int _tmain(int argc, _TCHAR* argv[])
{
	MyStruct val;
	scanf("%f", &val.fval);
	val.ival = *((int*)((void*)&val.fval));
	printf("sign = %lu,  exp = %lu,   mantisa = %lu", (val.ival>>31) & 0x01,
                            (val.ival >>23) & 0xff, val.ival  & 0x007fffff);
	getch();
	return 0;
}

