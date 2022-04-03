#include <iostream>
using namespace std;
#include<string> //包含 string 头文件


//定义结构体
 struct hero
{
    string name;//姓名

    int aeg;//年龄s

  string sex;//性别
};
//冒泡排序
 void bubbleSort(struct hero heroarr[], int len)
 {
     //外层循环轮数  元素长度 - 1
     for (int i = 0; i < len - 1; i++)
     {
         //内层循环   元素长度 - 当前轮数 - 1
         for (int j = 0; j < len - i - 1; j++)
         {
             //判断 j 下标的元素年龄大于 j+1 下标的元素年龄 交换他们
             if (heroarr[j].aeg > heroarr[j + 1].aeg)
             {
                 //创建相同类型的临时空间
                 struct hero temp = heroarr[j];
                  heroarr[j] = heroarr[j + 1];
                         heroarr[j + 1]= temp;
             }

         }
     }
 }
 //输出函数
 void printf(struct hero heroarr[], int len)
 {
     for (int i = 0; i < len; i++)
     {
         cout << "姓名：" << heroarr[i].name << "年龄：" << heroarr[i].aeg << "性别：" << heroarr[i].sex << endl;
     }
 }

int main()
{
    //1、创建结构体数组

   struct hero heroarr[5]=
    {   {"刘备",23,"男"},
        {"关羽",22,"男"},
        {"张飞",20,"男"},
        {"赵云",21,"男"},
        {"貂蝉",19,"女"},
    };
   int len = sizeof(heroarr) / sizeof(heroarr[0]);

   cout << "排序前的顺序：" << endl;
   for (int i = 0; i < len; i++)
   {
       cout << "姓名：" << heroarr[i].name << "年龄：" << heroarr[i].aeg << "性别：" << heroarr[i].sex << endl;
   }
    //2、利用冒泡排序升序排序
   bubbleSort( heroarr ,len);

    //3、打印输出后的排序结果

   cout << "排序后的顺序：" << endl;

    printf(heroarr, len);

    system("pause");
    return 0;
}