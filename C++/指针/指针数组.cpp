
#include <iostream>
using namespace std;

int main()
{
	//指针数组
	//利用指针来访问数组中的元素
	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int* p = arr;  //arr就是数组的首地址
	cout << "利用指针访问数组中第一个元素 " << *p << endl;

	p++;//让指针向后偏移四个字节
	cout << "利用指针访问数组中第二个元素 " << *p << endl;

	cout << "利用指针遍历数组" << endl;

	int* p1 = arr;
	for (int i = 0; i < 9; i++)
	{
		cout << *p1 << endl;
		p1++;
	}
	system("pause");
	return 0;
}
