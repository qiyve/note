#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用拷贝和替换算法  swap
//总结： swap交换容器时，注意交换的容器要同种类型

//swap(container  c1, container  c2);
//互换两个容器的元素
//c1 容器1
//c2 容器2

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
        v1.push_back(i);
        v2.push_back(i + 100);
    }

    cout << "交换前：" << endl;
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;

    cout << "------------------------" << endl;

    //交换两个v1 和 v2的元素
    swap(v1, v2);
    cout << "交换后：" << endl;

    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}