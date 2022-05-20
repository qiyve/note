#include<stdio.h>

//1、 * () 与[]是可以互换的，也就是说：
//* (*(p + 1) + 2) 相当与 p[1][2]
//那 * (p + 1)[2] 是否一定等于呢？ 通过反汇编进行论证。
void func()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	int(*px)[2];
	px = &arr;
	printf("%d \n", *(px + 1)[2]);
	printf("%d \n", px[1][2]);

}

//2、使用数组指针遍历一个一维数组.
void test()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	int(*px)[2] = &arr;

	for (int i = 0; i < 13; i++)
	{
		//printf("%d\n", *(*(px + 0) + i));
		printf("%d\n", px[0][i]);
	}
}

int main()
{
	func();
	//test();

	return 0;
}