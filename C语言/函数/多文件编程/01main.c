#include <stdio.h>
#include"02func.h"

int main()
{
	// gcc -o hello.exe 01main.c 02fun.c 02fun.h  head.h
	int a = 10;
	int b = 20;
	printf("%d\n", Max(a, b));

	system("pause");
	return 0;
}
