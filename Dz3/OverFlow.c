// HomeWork6.cpp : Переполнение стека функции. 
//

#include "stdafx.h"
#include <string.h>
#include <conio.h>
 
typedef void (*p_fun)(void);


	void a(){
			 printf("proc a\n");
		}
	void b(){
			printf("proc b\n");
		}

	struct MyStruct
	{
		p_fun pb;
		p_fun pa[2];
	};

	int _tmain(int argc, _TCHAR* argv[])
	{
		 MyStruct val;
		 val.pa[0]=&a;

		 val.pb = &b;
		(*val.pb)();   // вызывается b

		val.pa[-1]=&a; // Lol. Массив от -1 элемента :D
		(*val.pb)();   // вызывается a

		getch();
		return 0;
}