
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
    //2、创建结构体数组 
    
    //语法 ：struct 结构体名 数组名[元素个数] = { {}，{}....{} }；
    Student arr[2] = { 
        {"张三",15,60},
        {"李四",16,99}
    };

    //3、给结构体数组中的元素赋值
    arr[0].name = "阿三";
    arr[0].aeg = 30;
    arr[0].score = 1;

    //3、遍历结构体数组
    //cout << "姓名 ：" << arr[0].name << " 年龄：" << arr[0].aeg
    //<< " 分数：" << arr[0].score << endl;

    //利用循环打印输出
    for (int i = 0; i < 2; i++)
    {
        cout << "姓名 ：" << arr[i].name 
            << " 年龄 ：" << arr[i].aeg
            << " 分数 ：" << arr[i].score << endl;
    }

    system("pause");
    return 0;
}

