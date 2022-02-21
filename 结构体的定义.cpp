
#include <iostream>
using namespace std;
#include<string>

//1、创建学生数据类型： 学生包括（姓名，年龄，分数）
// 自定义的数据类型，一些类型集合组成的一个类型
//语法  struct 类型名称 {成员列表}
struct Student
{
    //成员列表

    //姓名
    string name;
    //年龄
    int aeg;
    //分数
    int score;
}s3;//顺便创建一个变量
     
//2、通过学生类型创建具体学生

int main()
{
 //  2.1、struct Student s1;
    //struct的关键字在结构体创建的时候可以省略，但是结构体定义不可以省略

    struct Student s1;
    //给s1属性赋值，通过 . 访问结构体变量中的属性
    s1.name = "张三";
    s1.aeg = 20;
    s1.score = 80;
    cout << "姓名：" << s1.name << " 年龄：" << s1.aeg << " 分数：" << s1.score << endl;

 //  2.2、struct  结构体名 变量名 ={成员1值，成员2值}
 
    struct Student s2 = { "李四",20,90 };

    cout << "姓名：" << s2.name << " 年龄：" << s2.aeg << " 分数：" << s2.score << endl;

 //  2.3、定义结构顺便创建变量

    s3.name = "王五";
    s3.aeg = 17;
    s3.score = 100;

    cout << "姓名：" << s3.name << " 年龄：" << s3.aeg << " 分数：" << s3.score << endl;

    system("pause");
    return 0;
}

