#include<iostream>
using namespace std;
#include<map>

//map容器 大小和交换

//size（）；          //返回容器中元素的数目
//empty();           //判断容器是否为空
//swap （）;          //交换两个集合容器

void printMap(map<int, int>& m)
{
	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
    }
	cout << endl;
}

//大小
void test01()
{
	map<int, int>m1;

	m1.insert(pair<int, int>(1, 10));
	m1.insert(pair<int, int>(2, 20));
	m1.insert(pair<int, int>(3, 30));
	m1.insert(pair<int, int>(4, 40));

	if (m1.empty())  //为真 容器为空
	{
		cout << "m1 为空" << endl;
	}
	else
	{
		cout << "m1 不为空" << endl;
		// 元素个数为
		cout << "m的大小为：" << m1.size() << endl;
	}

	
}

//交换
void test02()
{
	map<int, int>m1;

	m1.insert(pair<int, int>(1, 10));
	m1.insert(pair<int, int>(2, 20));
	m1.insert(pair<int, int>(3, 30));
	
	map<int, int>m2;
	m2.insert(pair<int, int>(4, 100));
	m2.insert(pair<int, int>(5, 200));
	m2.insert(pair<int, int>(6, 300));

	cout << "交换前 " << endl;
	printMap(m1);
	printMap(m2);

	//开始交换
	m2.swap(m1);

	cout << "---------------------" << endl;
	cout << "交换后 " << endl;
	printMap(m1);
	printMap(m2);
}
int main()
{
	test01();
	
	test02();

	system("pause");
	return 0;
}