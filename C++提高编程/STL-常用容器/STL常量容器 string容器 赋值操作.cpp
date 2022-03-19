#include<iostream>
using namespace std;
#include<string>
//string赋值操作

//1. string & operator=(const char* s);          //char*类型字符串，赋值给当前的字符串
//2. string & operator=(const string & s);       //char*类型字符串，赋值给当前的字符串
//3. string & operator=(char c)；                //字符赋值  给当前字符串
//4. string & assign = (const char* s);          //把字符串s赋值给当前字符串
//5. string & assign = (const char* s, int  n);  //把字符串s的前n个字符赋值给当前字符串
//6. string & assign = (const string & s);       //把字符串s赋值给当前字符串
//7 string & assign = (int n, char  c);          //用n个字符c赋值给当前字符串


void test01()
{
	string str1;      //char*类型字符串，赋值给当前的字符串
	str1 = "hello world";
	cout << "str1 = " << str1 << endl;

	string str2;     //char*类型字符串，赋值给当前的字符串
	str2 = str1;
	cout << "str2 = " << str2 << endl;

	string str3;    //字符赋值  给当前字符串
	str3 = 'a';
	cout << "str3 = " << str3 << endl;

	string str4;    //把字符串s赋值给当前字符串
	str4.assign("hello C++");
	cout << "str4 = " << str4 << endl;

	string str5;   //把 字符串s的 前n个 字符赋值给当前字符串
	str5.assign("abc", 2);
	cout << "str5 = " << str5 << endl;

	string str6;   //把字符串s赋值给当前字符串
	str6.assign(str5);
	cout << "str6 = " << str6 << endl;

	string str7;   //用n个 字符c 赋值给当前字符串
	str7.assign(5, 'c');
	cout << "str7 = " << str7<< endl;

}
int main()
{

	test01();

	

	system("pause");
	return 0;
}