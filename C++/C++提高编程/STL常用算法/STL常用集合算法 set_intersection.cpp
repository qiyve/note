#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用集合算法 set_intersection
//求两个容器的交集   交集：两个集合中重复的元素称为交集

//set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest); 4
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
        v2.push_back(i + 4); //4~13
    }


    vector<int>vTarget;
    //目标容器需要提前开辟空间
    //最特殊情况 大容器包含小容器  开辟空间 取小容器的size即可
    vTarget.resize(min(v1.size(), v2.size()));

    //获取交集
    vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());

    for_each(vTarget.begin(), itEnd, myPrint);
    cout << endl;
}
//总结：1.求交集的两个集合必须是有序序列
//      2.目标容器开辟空间需要两个容器中取最小值
//      3.set_intersection返回值是交集中最后一个元素的位置

int main()
{
    test01();

    system("pause");
    return 0;
}