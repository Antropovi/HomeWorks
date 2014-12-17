// Антропов И М Reavization of fast powing

#include "stdafx.h"


int main()
{
	int val = 0, pow = 0 , result = 1;
	scanf("%d\n",  &val);
	scanf("%d",  &pow);
	while (pow)
	{
        	if (!(pow & 1))
        	{
            		pow = pow >> 1;
			val *= val;
		}
		else
		{
			pow--;
			result *= val;
		}
	}

	printf("%d", result);

	return 0;
}

