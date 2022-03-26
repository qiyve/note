#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用排序算法 reverse

//reverse(iterator beg, iterator end);
//反转指定范围的元素
//beg 开始迭代器
//end 结束迭代器

class MyPrint
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
    cout << "反转前：" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;

    //反转
    reverse(v.begin(), v.end());

    cout << "反转后：" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
}
int main()
{

    test01();

    

    system("pause");
    return 0;
}