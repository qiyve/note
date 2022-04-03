#include<iostream>
using namespace std;
#include<list>

//list容器 插入和删除

//两端操作
//push_back(elem);         //从容器尾部加入一个元素
//pop_back();              //删除容器中最后一个元素
//push_front(elem)；       //在容器开头插入一个元素
//pop_front();             //从容器开头移除第一个元素

//指定插入
//insert(pos, elem);       //从容器pos位置插elem元素的拷贝，返回新数据的位置
//insert(pos, n, elem);    //从容器pos位置插n个elem数据，无返回值
//insert(pos, beg, end);   //从pos位置插入（beg ， end）区间的数据，无返回值

//指定删除
//clear( )；               //移除容器的所有数据
//erase（beg, end）;       //删除（beg ， end）区间的数据，返回下一个数据的位置
//erase(pos);              //删除pos位置的数据，返回下一个数据的位置
//remove(elem);            //删除容器中所有与elem值匹配的元素

void printList(const list<int>&L)
{    //限定只读
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


void test01()
{
	list<int>L1; 

	//尾插
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	
	//头插
	L1.push_front(1);
	L1.push_front(2);
	L1.push_front(3);
	// 3 2 1 10 20 30
	printList(L1);

	//尾删
	L1.pop_back();
	// 3 2 1 10 20 
	printList(L1);

	//头删
	L1.pop_front();
	// 2 1 10 20 
	printList(L1);

	//insert插入   // 位置必须是迭代器
	//L1.insert(L1.begin(), 100);
	//100 2 1 10 20 
	list<int>::iterator it = L1.begin();
	L1.insert(++it, 100);  //利用insert方式 迭代器位置是可以移动的
	//2  100  1  10  20
	printList(L1);

	//删除
	it = L1.begin();
	//L1.erase(it);
	//  100  1  10  20
	L1.erase(++it);
	//2 1 10 20
	printList(L1);

    //移除
	L1.push_back(1000);
	L1.push_back(1000);
	L1.push_back(1000);
	printList(L1);

	L1.remove(1000); //删除容器中所有与elem值匹配的元素
	printList(L1);

	//清空
	L1.clear();
	printList(L1);

}
 



int main()
{
	test01();
	


	system("pause");
	return 0;
}