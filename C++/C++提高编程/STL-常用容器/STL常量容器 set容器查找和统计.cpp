#include<iostream>
using namespace std;
#include<set>

//set容器  查找和统计


//find(key);            //查找key是否存在，返回该键的元素的迭代器；若不存在，返回set.end()；
//count(key);           //统计key的元素个数



//大小
void test01()
{
	//查找
	set<int>s1;
	
	//插入数据  只有insert方式
	s1.insert(10);
	s1.insert(40);
	s1.insert(20);
	s1.insert(30);

	set<int>::iterator pos = s1.find(50);

	if (pos != s1.end())//判断这个返回值 不等于end 查找到该元素 
	{
		cout << "找到元素" << *pos << endl;
	}
	else
	{
		cout << "未找到元素" << endl;
	}
}

//统计
void test02()
{
	set<int>s;
	s.insert(10);
	s.insert(30);
	s.insert(20);
	s.insert(40);
	s.insert(30);
	s.insert(30);


	//统计30的个数   //set容器中不允许有重复的元素
	int num1 = s.count(30);
	cout << "num1 = " << num1 << endl;

	int num2 = s.count(300);
	cout << "num2 = " << num2 << endl;
}

int main()
{
	//test01();
	
	test02();

	system("pause");
	return 0;
}