
#include <iostream>
using namespace std;

//指针和函数
void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
int main()
{
	int a = 20;
	int b = 10;
	//地址传递  如果是地址传递可以修饰实参
	//如果不想修改实参就用值传递 ；想修改实参就用地址传递
	swap(&a,& b);
	
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;

	system("pause");
	return 0;
}
