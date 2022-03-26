#include<iostream>
using namespace std;
#include<functional> //内建函数对象头文件
#include<algorithm>
#include<vector>

//内建函数对象 关系仿函数


//template <class T> bool equal_to<T>        //等于
//template <class T> bool not_equal_to<T>    //不等于         
//template <class T> bool  greater<T>        //大于
//template <class T> bool  greater_equal<T>  //大于等于
//template <class T> bool less <T>           //小于
//template <class T> bool less_equal<T>      //小于等于

class MyCompare
{
public:
	bool operator()(int v1,int v2)
	{
		return v1 > v2;
	}
};

//大于 greater
void test01()
{
	vector<int>v;

	v.push_back(10);
	v.push_back(30);
	v.push_back(40);
	v.push_back(20);

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//降序
	//sort(v.begin(), v.end(),MyCompare());
	sort(v.begin(), v.end(), greater<int>());

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
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