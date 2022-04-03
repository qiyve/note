#include<iostream>
using namespace std;
#include<vector>

// vector容器 预留空间
//reserve(int  len);  // 容器预留len个元素长度，预留位置不初始化，元素不可访问




void test01()
{
	vector<int>v;

	//利用reserve 预留空间
	v.reserve(100000);

	int num = 0;//统计开辟新空间次数
	int* p = NULL;//创建一个指针

	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);

		// 指针不等于 容器中 元素的首地址  就开辟一次空间
		if (p != &v[0])
		{
			p = &v[0]; //指向新开辟空间元素首地址

			num++; //统计开辟次数
		}
		
	}

	cout << " 开辟空间次数：" << num << endl;
}



int main()
{

	test01();

	

	system("pause");
	return 0;
}