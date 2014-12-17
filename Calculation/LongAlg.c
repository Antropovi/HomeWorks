// LongAlg.c Стековый калькулятор Антропов ИМ
//

#include <conio.h>
#include <stdlib.h>
#include <string.h> 
#include "stdafx.h"

int read_lexem(struct node **lexem){
	char c[2];

	*lexem = NULL;
	
	do{
		fgets(c, 2, stdin);
	}while(c[0]==' ' || c[0]=='\n' || c[0]=='\r');

	while(c[0]!=' ' && c[0]!='\n' && c[0]!='\r'){
		linkedList_Add(c[0], lexem);
		fgets(c, 2, stdin);
	}
	return c[0]!='\n' && c[0]!='\r';
}

int main()
{
	struct node *lexem;
	struct stack *stack = NULL;
	int flag_read_next;
	int flag_do_process = 1;//true

	flag_read_next = read_lexem(&lexem);
	while(lexem!=NULL){
		stack = stack_Add(stack, lexem);
		
		// если расчет еще не сломался
		// то прасчитываем дальше
		if(flag_do_process)
			flag_do_process = stack_Process(&stack);

		// если не прочли все до конца
		// то читаем дальше
		if(flag_read_next)
			flag_read_next = read_lexem(&lexem);
		else
			lexem=NULL;
	}

	stack_Print(stack);

	stack_Free(stack);

	getch();
	return 0;
}

