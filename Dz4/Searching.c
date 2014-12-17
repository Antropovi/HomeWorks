// Searching.c : Реализация наивного поиска подстроки в строке
// Антропов ИМ

#include "stdafx.h"
#include <string.h>

int copmpare(int i, char firststring[100], char secondstring[100])
{
    int j = 0;

    for (j = 0; secondstring[j] != 0 && firststring[j+i] != 0; j++)
    {
        if (firststring[j+i] != secondstring[j]) return 0;
    }

    return secondstring[j] == 0 ? 1 : 0;

}


int main()
{
	char firststring[100] = "";
	char secondstring[100] = "";
    
	scanf("%s", firststring);
	scanf("%s", secondstring);
	int i = 0, count = 0;
	for (i = 0; firststring[i] != 0; i++)
	{
		if (firststring[i]==secondstring[0]) 
		{
			if (copmpare(i,firststring,secondstring))
			{
				++count;
			}

		}
	}


	printf("%d", count);

	return 0;
}


