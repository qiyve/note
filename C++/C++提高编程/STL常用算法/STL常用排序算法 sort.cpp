#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<functional>

//常用排序算法 sort

//sort(iterator beg, iterator  end, _Pred) ；
//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
// beg  开始迭代器
// end  结束迭代器
// _Pred 谓词

void MyPrint(int val)
{
    cout << val << endl;
}

void test01()
{
    vector<int>v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);
    v.push_back(50);

    //利用sort进行升序
    sort(v.begin(), v.end());
    for_each(v.begin(), v.end(), MyPrint);//普通函数只需要 写函数名即可
    cout << endl;
    //改变为 降序
    sort(v.begin(), v.end(), greater<int>());
    for_each(v.begin(), v.end(), MyPrint);
}
int main()
{
    test01();

    

    system("pause");
    return 0;
}