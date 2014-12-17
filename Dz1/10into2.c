// Антропов И М Perevod from 10 into 2

#include <stdio.h>
#include <stdlib.h>
 
 
int main()
{
	char result[sizeof(int) * 8] = "   ";
	int counter = 0;
	int val = 0;
	unsigned int valwithoutsign;

	scanf("%d",  &val);
	valwithoutsign = (unsigned int)val;
	counter = sizeof(result) - 2; // nuber of last elem of array

	while(valwithoutsign != 0 && counter > 0)
    	{
        	result[counter] = '0'  + (valwithoutsign % 2);
		valwithoutsign /= 2;
		counter--;
	}

	printf("%s", result);
	
	return 0;
}
