#include <iostream>
using namespace std;
#include<vector>
#include<algorithm>

//常用查找算法 count_if

//count_if(iterator beg, iterator end, _pred);
//按条件统计元素出现次数            
//beg 开始迭代器
//end 结束迭代器
//_pred  谓词


//统统内置数据类型
class Greater20
{
public:

    bool operator()(int val)
    {
        return val > 20;
    }
};
void test01()
{
    vector<int>v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);
    v.push_back(50);

    int num = count_if(v.begin(), v.end(), Greater20());

    cout << "大于20的元素个数为：" << num << endl;
}

//统计自定义数据类型
class  Person
{
public:
    Person(string name,int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
  

    string m_Name;
    int m_Age;
};

class Greater25
{
public:

    bool operator()(const Person& p)
    {
        return p.m_Age > 25;
    }
};

void test02()
{
    vector<Person>v;

    Person p1("aaa", 35);
    Person p2("bbb", 25);
    Person p3("ccc", 20); 
    Person p4("ddd", 35);
    Person p5("eee", 25);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    //统计年龄大于 25的人数
   int num = count_if(v.begin(), v.end(), Greater25());

   cout << "统计年龄大于25的人数：" << num << endl;
}
int main()
{
    //test01();

    test02();

    system("pause");
    return 0;
}