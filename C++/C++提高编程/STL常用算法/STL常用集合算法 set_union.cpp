#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用集合算法   set_union
//求两个集合的并集   

//set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
//注意：两个集合必须是有序序列
//beg1  容器1 开始迭代器
//end1  容器1 结束迭代器
//beg2  容器2 开始迭代器
//end2  容器2 结束迭代器
//dest   目标容器开始迭代器

void myPrint(int val)
{
    cout << val << " ";
}

void test01()
{
    vector<int>v1;
    vector<int>v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i); //0~9
        v2.push_back(i + 5); //4~14
    }
    vector<int>vTarget;
    //目标容器需要提前开辟空间
    //最特殊情况 两个容器没有交集，并集就是两个容器的size相加
    vTarget.resize(v1.size() + v2.size());

    vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), itEnd, myPrint);
    cout << endl;
}

//总结： 求并集的两个集合必须的有序序列
//       目标容器开辟空间需要两个容器相加
//       set_union返回值既是并集中最后一个元素的位置

int main()
{
    test01();

    system("pause");
    return 0;
}