// Антропов ИМ : Внутренности float. 2 способ
//

#include "stdafx.h"
#define maxexp 255

struct MyStruct
{
	union 
	{
		long unsigned ival;
		float fval;
	} val;

};

int main()
{
	MyStruct val;
	float valin = 0, valout = 0;
	scanf("%f",&valin);
	scanf("%f",&valout);
	
	val.val.fval = valin / valout;
	unsigned exp = (val.val.ival >> 23) & 0xff;
	unsigned sign = (val.val.ival > >31) & 0x01;
	unsigned mantissa = (val.val.ival & 0x007fffff);
	
	if (exp==maxexp && !mantissa) 
	{
		if (!sign) printf ("infinity"); else printf ("-infinity");
	}
	else 
	{
		if (exp==maxexp && mantissa) 
		{
			printf("NaN");
		}
		else
		{
			if (!exp && !mantissa)
			{
				printf("fval=0");
			}
			else
			{
				printf("fval = (-1)^%d*2^%d*1.%lu ", sign, exp-127, mantissa);
			}
		}
	}	
	return 0;
}

