#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用拷贝和替换算法  replace
//总结:replace会替换区间内满足条件的元素

//replace(iterator beg, iterator end, oldvalue, newvalue);
//将区间内旧容器 替换成 新元素
//beg 开始迭代器
//end 结束迭代器
//oldvalue  旧元素
//newvalue 新元素

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
    vector<int>v1;
   
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    v1.push_back(30);

    cout << "替换前：" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;

    //把容器中30 替换成 300
    replace(v1.begin(), v1.end(), 30, 300);

    cout << "替换后：" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;
}

int main()
{

    test01();

    

    system("pause");
    return 0;
}