#include<iostream>
using namespace std;
#include<vector>

// vector容器互换
// swap ( vec ）；  // 将vec与本身的元素互换

void printVector(vector<int>&v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//1、基本使用
void test01()
{
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}

	cout << "交换前 ：" << endl;
	printVector(v1);

	vector<int>v2;
	for (int i = 10; i > 0; i--)
	{
		v2.push_back(i);
	}
	printVector(v2);


	cout << "交换后 ：" << endl;
	v1.swap(v2);
	printVector(v1);
	printVector(v2);
}

//2、实际用途 
//巧用swap可以收缩空间
void test02()
{
	vector<int>v;
	for (int i = 0; i < 1000; i++)
	{
		v.push_back(i);
	}

	cout << "V 的容量：" << v.capacity() << endl;
	cout << "V 的大小：" << v.size() << endl;

	//重新定义大小
	v.resize(3);
	cout << "V 的容量：" << v.capacity() << endl;
	cout << "V 的大小：" << v.size() << endl;

	//巧用swap收缩空间
	vector<int>(v).swap(v);
	cout << "V 的容量：" << v.capacity() << endl;
	cout << "V 的大小：" << v.size() << endl;
}


int main()
{

	//test01();

	test02();

	system("pause");
	return 0;
}