#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

//仿函数 返回值类型是bool数据类型 称为谓词
//如果operator()接收一个参数，那么叫做一元谓词
//如果operator()接收两个参数，那么叫做二元谓词

//谓词 二元谓词

class GreaterFive
{
public:

	bool operator()(int val1,int val2)
	{
		return val1 > val2;//降序
	}
};

void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);

	sort(v.begin(),v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << "----------------" << endl;
	//使用函数对象 改变算法策略， 变为排序规则为从大到小

	sort(v.begin(), v.end(), GreaterFive());//GreaterFive() 匿名函数对象
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