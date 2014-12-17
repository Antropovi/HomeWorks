// Антропов И М Perevod from 10 into 2

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 

 
int main(int argc, char **argv)
{
    char a[sizeof(int) * 8] = "   ";
    int i = 0;
	int k = 0;
	unsigned int k1;

	scanf("%d",  &k);
	k1 = (unsigned int)k;
	i=sizeof(a) - 2; // nuber of last elem of array

	 while(k1 != 0 && i > 0)
    {
        a[i] = '0'  + (k1 % 2);
		k1 /= 2;
		i--;
	}

	printf("%s", a);
	getch();
	return 0;
}
