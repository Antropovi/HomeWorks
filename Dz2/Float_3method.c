// HomeWork3.cpp : Вывод float. 3 способ
//

#include "stdafx.h"
#include <conio.h>


union val
{
 float f;
 struct {
		  unsigned int mantissa:23;
		  unsigned int  exp:8;
		  unsigned int sign:1;
 } image;
};


int _tmain(int argc, _TCHAR* argv[])
{
	val fval;
	scanf("%f",&fval.f);
	if (fval.image.exp==255 && fval.image.mantissa) {
		if (fval.image.sign) printf ("infinity"); else printf ("-infinity");
	}
	else 
		if (fval.image.exp && !fval.image.mantissa) printf("NaN");
		else 
			if (!fval.image.exp && !fval.image.mantissa) printf("fval=0");
			else
			{
				printf("fval = (-1)^%d*2^%d*1.%lu ",  fval.image.sign, fval.image.exp-127, fval.image.mantissa);
			}
	getch();
	return 0;
}

