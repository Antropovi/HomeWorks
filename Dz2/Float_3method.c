// Антропов ИМ : Вывод float. 3 способ
//

#include "stdafx.h"
#define maxexp 255

union val
{
 	float f;
 	struct 
 	{
		unsigned int mantissa:23;
		unsigned int  exp:8;
		unsigned int sign:1;
 	} image;
};


int main()
{
	val fval;
	float firstval = 0, secondval = 0;
	scanf("%f",&firstval);
	scanf("%f",&secondval);
	fval.f= ferstval / secondval;
	
	if (fval.image.exp==maxexp && !fval.image.mantissa)
	{
		if (!fval.image.sign)
		{
			printf ("infinity")
		}
		else 
		{
			printf ("-infinity");
		}
			
	}
	else
	{
		if (fval.image.exp==maxexp && fval.image.mantissa) 
		{
			printf("NaN");
		}
		else
		{
			if (!fval.image.exp && !fval.image.mantissa)
			{
				printf("fval=0");
			}
			else
			{
				printf("fval = (-1)^%d*2^%d*1.%lu ",  fval.image.sign, fval.image.exp-127, fval.image.mantissa);
			}
		}
	}	

	return 0;
}

