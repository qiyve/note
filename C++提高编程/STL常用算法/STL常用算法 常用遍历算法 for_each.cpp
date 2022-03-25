#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


//常用遍历算法 for_each

//for_each(iterator beg, interator end, _func);
//遍历算法遍历容器元素
//beg开始迭代器
//end结束迭代器
//_func函数或者函数对象

//普通函数
void Print(int val)
{
	cout << val << " ";
}
//仿函数
class Print02
{
public:

	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), Print);
	cout << endl;


	for_each(v.begin(), v.end(), Print02());
	cout << endl;
}


int main()
{
	test01();
	

	system("pause");
	return 0;
}