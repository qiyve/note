
#include <iostream>
using namespace std;
#include<string> //包含 string 头文件
#include<ctime>  //时间头文件

//1、定义学生结构体
struct Student
{
    string sName;// 姓名
    int score;// 分数
};
//老师的结构体定义
struct Teacher
{     //姓名
    string tName;
    //学生数组
    struct Student sArray[5] ;
};
//给老师和学生复制的函数
void allocatespace(struct Teacher tArray[], int len)
{
    string nameSeed = "ABCDE";
    //给老师赋值
    for (int i = 0; i < len; i++)
    {
        tArray[i].tName = "Teacher_";
        tArray[i].tName += nameSeed[i];

        //通过循环给每个老师带的学生赋值
        for (int j = 0; j < 5; j++)
        {
            tArray[i].sArray[j].sName = "Student_";
            tArray[i].sArray[j].sName += nameSeed[j];

            int ranom = rand() % 61+40;//40~100
            tArray[i].sArray[j].score = ranom;
        }
    }

}
//打印函数
void printinfo(struct Teacher tArray[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "老师的姓名：" << tArray[i].tName << endl;

        for (int j = 0; j < 5; j++)
        {
            cout <<"\t`学生的姓名：" << tArray[i].sArray[j].sName << " 分数：" << tArray[i].sArray[j].score << endl;
        }
    }
}

int main()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    //1、创建3名老师的数组
    struct Teacher tArray[3];
    //2、通过函数给3名老师的信息赋值，并给老师带的学生信息赋值

    int len = sizeof(tArray) / sizeof(tArray[0]);
    allocatespace(tArray, len);

    //3、打印所有老师及所带学生信息
    printinfo(tArray, len);


    system("pause");
    return 0;
}

