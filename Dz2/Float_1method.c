// Антропов ИМ : Внутренности float. Первый способ
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
	float a,b;
	scanf("%f",&a);
	scanf("%f",&b);
	val.fval=a/b;
	val.ival = *((int*)((void*)&val.fval));
	unsigned exp = (val.ival >>23) & 0xff;
	unsigned sign = (val.ival>>31) & 0x01;
	unsigned mantissa=(val.ival  & 0x007fffff);
	if (exp==255 && !mantissa) {
		if (!sign) printf ("infinity"); else printf ("-infinity");
	}
	else 
		if (exp==255 && mantissa) printf("NaN");
		else 
			if (!exp && !mantissa) printf("fval=0");
			else
			{
				printf("fval = (-1)^%d*2^%d*1.%lu ", sign, exp-127, mantissa);
			}
}

