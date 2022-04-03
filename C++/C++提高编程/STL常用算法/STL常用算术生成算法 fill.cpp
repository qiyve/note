#include <iostream>
using namespace std;
#include<vector>
#include<numeric>
#include<algorithm>


//常用算术生成算法  fill
//总结：利用fill 可以将容器区间内元素填充为 指定的值

//fill(iterator  beg, iterator  end, value);
//向容器中填充元素
//beg 开始迭代器
//end 结束迭代器
//value 填充的值

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
    v.resize(10);

    cout << "填充前：" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;

    //后期重新填充
    
    fill(v.begin(), v.end(), 100);
    cout << "填充后：" << endl;
    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}