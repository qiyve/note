#include <stdio.h>

void swap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}
//指针作为函数参数
void swap02(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int main()
{
	int a = 10;
	int b = 20;

	//值传递 形参不影响实参的值
	/*swap01(a, b);
	printf("%d\n", a);
	printf("%d\n", b);*/

	//地址传递 形参会影响实参
	swap02(&a, &b);
	printf("%d\n", a);
	printf("%d\n", b);

	system("pause");
	return 0;
}
