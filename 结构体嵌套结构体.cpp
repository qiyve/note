
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
//定义老师的结构体
struct Teacher
{
    int id; //教师编号
    string name;//教师姓名
    int age;//教师年龄
    Student stu;//辅导的学生
};
//在结构体中可以定义另一个结构体作为成员来解决一些实际问题
int main()
{
    //结构体嵌套结构体
    //创建老师
    Teacher t;
    t.id = 001;
    t.name = "老李";
    t.age = 48;
    t.stu.name = "小王";
    t.stu.aeg = 17;
    t.stu.score = 88;


    cout << "老师的姓名：" << t.name
        << " 编号：" << t.age
        << " 年龄：" << t.age
        << " 老师辅导的学生姓名：" 
        << t.stu.name<< " 学生年龄：" << t.stu.aeg
        << " 学生分数：" << t.stu.score << endl;

    system("pause");
    return 0;
}

