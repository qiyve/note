#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>


//常用查找算法  binary_search

//bool binary_search(iterator beg, iterator end, value);
//查找指定的元素 查到返回true 否则返回false
//注意：在 无序序列中不可用
//beg 开始迭代器
//end 结束迭代器
//value 查找的元素

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	v.push_back(2);
	//查找容器中是否有6 元素
	//注意： 容器中必须是有序的序列 
	bool ret = binary_search(v.begin(), v.end(), 6);

	if (ret)
	{
		cout << "找到元素：" << endl;
	}
	else
	{
		cout << "未找到元素" << endl;
	}
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}