#include<iostream>
using namespace std;
#include<list>

//list容器 赋值和交换

//size();              //返回容器中元素的个数
//empty（）；          //判断容器是否为空
//resize();            //重新定义容器的长度位 num，若容器变长，则以默认值填充新位置
					   //若容器变短，则末尾超出容器长度的元素被删除
//resize（num, elem）; //重新定义容器的长度为num，若容器边长，则以elem值填充新位置
					   //若容器变短，则末尾超出容器长度的元素被删除

void printList(const list<int>&L)
{    //限定只读
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//赋值
void test01()
{
	list<int>L1; 

	//添加数据
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	printList(L1);

	//判断容器是否为空
	if (L1.empty())
	{
		cout << "L1 为空" << endl;
	}
	else
	{
		cout << "L1 不为空" << endl;
		cout << "L1的元素个数：" << L1.size() << endl; //容器中元素个数
	}

	//重新指定大小
	//L1.resize(10); //容器变长 以默认值0 填充
	L1.resize(2);    //容器变短 删除超出容器元素 
	//10 20 
	printList(L1);

	//指定n个elem填充
	L1.resize(10, 100);
	//10 20 100...
	printList(L1);
}

int main()
{
	test01();
	


	system("pause");
	return 0;
}