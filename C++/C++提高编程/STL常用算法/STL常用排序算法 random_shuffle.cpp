#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<ctime>

//常用排序算法 random_shuffle

//random_shuffle(iterator beg, itreator end);
//指定范围内元素随机调整次序
//beg 开始迭代器
//end 结束迭代器

void MyPrint(int val)
{
    cout << val << " ";
}
void test01()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    vector<int>v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //利用洗牌 算法 打乱顺序
    random_shuffle(v.begin(), v.end());

    for_each(v.begin(), v.end(), MyPrint);
    cout << endl;
}
int main()
{

    test01();

    

    system("pause");
    return 0;
}