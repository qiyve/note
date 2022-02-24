
#include <iostream>
using namespace std;
#include<string> //包含 string 头文件

//1、定义结构体
struct Student
{
   // 成员列表
       // 姓名
    string name;
       // 年龄
    int aeg;
       // 分数
    int score;
};
int main()
{
    //1、创建学生结构体变量
    Student s = { "阿三",15,80 };

    //2、通过指针指向结构体
    Student* p = &s;

    //3、通过指针访问结构体变量中的数据
    //通过结构体指针 访问结构体中的属性 需要利用操作符 "->"
    cout << "姓名：" << p->name 
         << " 年龄：" << p->aeg 
         << " 分数：" << p->score << endl;

    system("pause");
    return 0;
}

