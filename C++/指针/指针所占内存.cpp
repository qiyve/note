
#include <iostream>
using namespace std;

int main()
{
	//指针所占的内存空间
	int a = 0;
	// int* p ;
	//p = &a;

	int* p = &a;
	// 在32位操作系统下，占4个字节， 不管是什么数据都是 4 个字节
	//64位下站8个字节
	
	cout << "sizeof(int) = " << sizeof(int *) << endl;
	cout << "sizeof(int) = " << sizeof(float*) << endl;
	cout << "sizeof(int) = " << sizeof(double*) << endl;
	cout << "sizeof(int) = " << sizeof(char*) << endl;
	system("pause");
	return 0;
}
