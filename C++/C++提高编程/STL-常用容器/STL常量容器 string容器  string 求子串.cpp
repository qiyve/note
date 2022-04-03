#include<iostream>
using namespace std;
#include<string>

//string 求子串

//string  substr （int pos = 0，int  n = npos）const； //返回由pos开始的n个字符组成的字符串 

void test01()
{
	string str = "abcdefg";

	string substr = str.substr(0, 3);

	cout << "substr = " << substr << endl;
}

//使用操作
void test02()
{
	string email = "asan@sina.com";

	//从邮件地址中 获取 用户信息

	int pos = email.find("@");

	string usrName = email.substr(0, pos);

	cout << "用户姓名" << usrName << endl;

}

int main()
{

	test01();

	test02();

	system("pause");
	return 0;
}