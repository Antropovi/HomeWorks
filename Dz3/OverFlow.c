// HomeWork6.cpp : Owerflow 
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
		(*val.pb)();   // called b

		val.pa[-1]=&a; // Lol. Massive from -1 elem
		(*val.pb)();   // called a instead b

		getch();
		return 0;
}
