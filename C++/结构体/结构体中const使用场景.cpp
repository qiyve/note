
#include <iostream>
using namespace std;
#include<string> //包含 string 头文件

//1、定义学生结构体
struct Student
{
    string name;// 姓名
    int aeg; // 年龄
    int score;// 分数
};
//将函数中的形参改为指针，可以减少内存空间，而且不会复制新的副本出来
void printStudent(const Student *s)  
{
   // s->aeg = 100; // 加入const之后 一旦有修改的操作就会报错，防止我们的误操作

    cout << "子函数中 姓名：" << s->name << " 年龄：" << s->aeg << " 分数：" << s->score << endl;
};
int main()
{
    //const 使用场景
    //创建一个结构体变量
    struct Student s = { "阿三",15,85 };

    //打印输出
    printStudent(&s);

    cout << "main函数中 姓名:" << s.name << " 年龄：" << s.aeg << " 分数：" << s.score << endl;

    system("pause");
    return 0;
}

