#include<iostream>
using namespace std;
#include<vector>

// vector  容量和大小

// empty（);                 // 判断容器是否为空
// capacity（）；            // 容器容量
// size（）；                // 返回容器中元素的个数
// resize（int  num ）；     // {重新定义容器的长度为num，若容器边长，则以默认值填充新位置
						     // 如果容器变短，则末尾超出容器长度的元素被删除}

///resize （int num，elem); // {重新定义容器长度为num，若容器变长，则以elem值填充新位置
							// 如果容器变短，则末尾超出容器长度的元素被删除}

void printVector(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

// vector容器 容量和大小关系 ：容量 大于等于 大小
void test01()
{
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1);
	
	if (v1.empty()) //为真  代表容器为空
	{
		cout << "v1 为空" << endl;
	}
	else
	{
		cout << "v1 不为空" << endl;
		cout << "v1的容量为：" << v1.capacity() << endl;
		cout << "v1的大小:" << v1.size() << endl;
	}

	//重新指定大小
	//v1.resize(20); //如果重新定义的比原来长了，默认用0填充
    v1.resize(20, 10); //利用重载版本，可以指定默认填充值，参数2
	printVector(v1);

	v1.resize(5);  //如果重新定义的比原来短了，删除末尾超出元素
	printVector(v1);
}



int main()
{

	test01();


	system("pause");
	return 0;
}