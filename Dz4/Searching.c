// Searching.c : Реализация наивного поиска подстроки в строке
// Антропов ИМ

#include "stdafx.h"
#include <string.h>

int finding (int i, char FirstString[100], char SecondString[100])
{
    int j = 0;

    for (j = 0; SecondString[j] != 0 && FirstString[j+i] != 0; j++)
    {
        if (FirstString[j+i] != SecondString[j]) return 0;
    }

    return SecondString[j] == 0 ? 1 : 0;

}


int main()
{
	char FirstString[100] = "";
	char SecondString[100] = "";
    
	scanf("%s", FirstString);
	scanf("%s", SecondString);
	int i = 0, count = 0;
	for (i = 0; FirstString[i] != 0; i++)
	{
		if (FirstString[i]==SecondString[0]) 
		{
			if ( finding(i,FirstString,SecondString) )
			{
				++count;
			}

		}
	}


	printf("%d", count);

	return 0;
}


