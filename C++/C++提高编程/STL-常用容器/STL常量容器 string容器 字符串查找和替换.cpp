#include<iostream>
using namespace std;
#include<string>

//字符串的查找和替换

//1、查找
void test01()
{

	string str1 = "abcdefgde";

	//int find(const string & str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找

	int pos =str1.find("de"); //从0号下标索引

	if (pos == -1)
	{
		cout << "未找到字符串" << endl;
	}
	else
	{
		cout << "找到字符串，pos = " << pos << endl;
	}

	//rfind 和find区别
	//rfind 是从右往左查，  find 是从左往右查
	 pos =str1.rfind("de");
	cout << "pos = " << pos << endl;
}

//2、替换
void test02()
{
	string str2 = "abcdefg";
	str2.replace(1, 3, "1111");

	cout << "str2 = " << str2 << endl;
}

int main()
{

	test01();

	test02();
	

	system("pause");
	return 0;
}