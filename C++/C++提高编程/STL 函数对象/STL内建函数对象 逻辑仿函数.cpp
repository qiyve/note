#include<iostream>
using namespace std;
#include<vector>
#include<functional> //内建函数对象头文件
#include<algorithm>

//内建函数对象  逻辑仿函数

//template <class T> bool logical_and<T>     //逻辑与
//template <class T> bool logical_or<T>      //逻辑或
//template <class T> bool logical_not<T>     //逻辑非

//逻辑非
void test01()
{
	vector<bool>v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(false);

	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//利用逻辑非 将容器v 搬运到 容器v2中， 并执行取反操作
	vector<bool>v2;
	v2.resize(v.size()); //搬运时先指定大小 

//参数1：原容器起始迭代器， 参数2：原容器结束迭代器，参数3：目标起始迭代器，参数4：仿函数
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());

	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


int main()
{
	test01();
	

	system("pause");
	return 0;
}