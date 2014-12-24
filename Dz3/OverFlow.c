// HomeWork6.cpp : Owerflow  переполнение стека
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


void overflow(char str[]) 
{
 char buffer[4];
 printf("buffer %p\n", buffer);
 printf("Stack:\n");
 printf("\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n");

 strcpy(buffer, str);

 printf("Stack:\n");
 printf("\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n\t%p\n");
}

void login() 
{
  printf("\nSomething going wrong\n");
}

int main(void) 
{
  char str[] = "TwelveSymbol    " ;     //12 symbol + hack address
  memmove(str+12, &login, 4);
  printf("str[12]: %p login: %p  main: %p\n", (void*)(str+12), &login, &main);
  overflow(str);
  return 0;
}
