// Антропов И М: Sign of nuber. 
//

#include "stdafx.h"
#include <conio.h>

int main()
{
	int val;
	scanf("%d", &val);

	printf("%d\n", (val >> (sizeof(int) << 3 - 1) ) | (!!val));

	getch();
	return 0;
}

