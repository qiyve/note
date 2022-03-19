#include<iostream>
using namespace std;
#include<string>

//字符串比较
//字符串比较是按字符的 ASCII码进行对比

void test01()
{
	string str1 = "aello";
	string str2 = "hello";

	if (str1.compare(str2) == 0)
	{
		cout << "str1 等于 str2" << endl;
	}
	else if(str1.compare(str2) > 0)
	{
		cout << "str1 大于 str2" << endl;
	}
	else 
	{
		cout << "str1 小于 str2" << endl;
	}
}

int main()
{

	test01();


	system("pause");
	return 0;
}