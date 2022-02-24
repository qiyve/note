
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
//值传递
void printStudent(Student s)
{
    s.aeg = 50;
    cout << "在子函数中 姓名：" << s.name << " 年龄：" << s.aeg << " 分数：" << s.score << endl;
};

//地址传递
void printStudent1(Student *p)
{
    p->aeg = 99;
    cout << "在子函数1中 学生姓名：" <<p-> name << " 年龄：" <<p-> aeg << " 分数：" <<p->score << endl;
};
int main()
{
    //结构体做函数
    //将学生传入到一个参数中，打印学生身上的所有信息

    Student s;
    s.name = "阿三";
    s.aeg = 15;
    s.score = 99;
     
    //打印输出
    printStudent(s);

   printStudent1(&s);

    cout<<"在 main函数中 姓名：" << s.name << " 年龄：" << s.aeg << " 分数：" << s.score << endl;
    
    // 如果不想修改主函数中的数据，用值传递，反之用地址传递
    system("pause");
    return 0;
}

