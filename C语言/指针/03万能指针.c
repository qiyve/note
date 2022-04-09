#include <stdio.h>



int main()
{
	int a = 10;
	//int* p = &a;
	//万能指针可以接收任意类型变量的内存地址
	void* p = &a;
	//再通过万能指针修改便便变量的值时 需要找到对应的指针类型
	*(int*)p = 100;
	printf("%d\n", a);
	printf("%d\n", *(int*)p);

	printf("%p\n", p);
	printf("万能指针所占字节：%d\n", sizeof(void*));
	//printf("void所占字节：%d\n", sizeof(void));


	system("pause");
	return 0;
}