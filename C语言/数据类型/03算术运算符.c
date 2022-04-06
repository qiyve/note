#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	

int main01()
{
	//0不能作为除数
	int a = 10;
	int b = 3;
	//两个整形相除结果还是整形  
	printf("%d\n", a / b);
	//取模 求余数 只能对整形惭怍
	printf("%d\n", a % b);


	return 0;
}

int main02()
{
	int a = 10;
	//a = a + 1;
	//a++; //后自增 在表达式计算后 在进性++ 
	//++a; //前自增 在表达式计算前 先进性++
	//int b = ++a * 10;
	int b = a++ * 10;

	printf("%d\n", b);
	printf("%d\n", a);

 
	return 0;
}

int main()
{
	int a = 10;
	a--;

	printf("%d\n",a);

	return;
}