#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用拷贝和替换算法  replace

//replace_if(iterator beg, iteraor end, _pred, newvalue);
//按条件替换元素， 满足条件的替换成指定元素
//beg 开始迭代器
//end 结束迭代器
//_Pred 谓词
// newvalue  替换的新元素

class MyPrint
{
public:

    void operator()(int val)
    {
        cout << val << " ";
    }
};

class Greater30
{
public:
    bool operator()(int val)
    {
        return val >= 20;
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

    cout << "替换前" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;

    //将大于等于20 替换为2000
    replace_if(v1.begin(), v1.end(),Greater30(),2000);

    cout << "替换后" << endl;
    for_each(v1.begin(), v1.end(), MyPrint());
    cout << endl;

  
}

int main()
{

    test01();



    system("pause");
    return 0;
}