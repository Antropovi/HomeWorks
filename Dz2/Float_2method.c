// HomeWork4.cpp : Вывод внутренностей float 2ым способом
//

#include "stdafx.h"
#include <conio.h>

struct MyStruct
{
	union 
	{
		long unsigned ival;
		float fval;
	} val;

};

int _tmain(int argc, _TCHAR* argv[])
{

	MyStruct val;
	scanf("%f", &val.val.fval);
	printf("sign = %lu,  exp = %lu,   mantisa = %lu", (val.val.ival>>31) & 0x01,
  (val.val.ival >>23) & 0xff, val.val.ival  & 0x007fffff);
	getch();
	return 0;
}

