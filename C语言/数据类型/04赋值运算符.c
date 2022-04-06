#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	

int main()
{
	int a = 10;

	a += 5;
	printf("%d\n", a);

	a %= 5;
	printf("%d\n", a);
	return;
}