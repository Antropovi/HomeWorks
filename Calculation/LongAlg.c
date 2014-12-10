// LongAlg.cpp : Defines the entry point for the console application.
//

#include <conio.h>
#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"

int main()
{
	char InPutString[256];
	char *tok;

	struct stack *stack = NULL;

	fgets(InPutString, 256, stdin);
	tok = strtok(InPutString, " \r\n");
	while(tok!=NULL){
		stack = stack_Add(stack, tok);
		
		stack = stack_Process(stack);

		tok = strtok(NULL, " \r\n");
	}

	stack_Print(stack);

	stack_Free(stack);

	getch();
	return 0;
}

