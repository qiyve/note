#include <iostream>
using namespace std;
    //函数的常见样式：
    //1、 无参无返
void test01()
{
    cout << "hello ward" << endl;
}

    //2、 有参无返
void test02(int a)
{
    cout << "hello ward a= " <<a<< endl;
}

    //3、 无参有返
int test03()
{
    cout << "hello ward" << endl;
    return 0;
}

    //4、 有参有返
int tese04(int a)
{
    
    cout << "hello ward" << endl;
    return a;
}

int main()
{
    //1、无参无返的函数调用
    test01();
	
    //2、 有参无返函数调用
    test02(100);

    //3、 无参有返调用
   int num1= test03();
   cout << "num1=" << num1 << endl;

    //4、 有参有返调用
   int b = tese04(100);
   cout << "b=" << b << endl;

	system("pause");
		return 0;
}