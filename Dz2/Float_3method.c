// HomeWork3.cpp : Вывод внутренностей float. 3-ий способ
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
	printf("manticssa %lu, exp %d, sign %d", fval.image.mantissa, fval.image.exp, fval.image.sign);
	getch();
	return 0;
}

