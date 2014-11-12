// HomeWork9.c : Поиск подстроки в строке 
// Антропов Игорь

#include "stdafx.h"
#include <string.h>

	char FirstString[100]="";
	char SecondString[100]="";


int finding (int i){
 int j;
 for (j=0; SecondString[j]!=0 && FirstString[j+i]!=0; j++){
  if (FirstString[j+i]!=SecondString[j]) return 0;
 }
 return SecondString[j]==0 ? 1 : 0;

}


int main()
{
	scanf("%s", FirstString);
	scanf("%s", SecondString);
	int i=0;
	for (i=0; FirstString[i]!=0; i++)
	{
		if (FirstString[i]==SecondString[0]) 
		{
			if ( finding(i) )
			{
				break;
			}

		}
	}

	if(FirstString[i]!=0)
	{
	    printf("%d", i);
	}
	else
	{
	printf("not found");
	}
	

	return 0;
}


