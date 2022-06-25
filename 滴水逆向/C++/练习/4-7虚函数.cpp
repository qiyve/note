#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//1、单继承无函数覆盖(打印Sub对象的虚函数表)
struct Base1
{
public:
    virtual void Function_1()
    {
        printf("Base:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Base:Function_2...\n");
    }
    virtual void Function_3()
    {
        printf("Base:Function_3...\n");
    }
};
struct Sub1 :Base1
{
public:
    virtual void Function_4()
    {
        printf("Sub:Function_4...\n");
    }
    virtual void Function_5()
    {
        printf("Sub:Function_5...\n");
    }
    virtual void Function_6()
    {
        printf("Sub:Function_6...\n");
    }
};

void test()
{
    //查看 Sub 的虚函数表		
    Sub1 s;
    //对象的前四个字节就是虚函数表				
    printf("Sub 的虚函数表地址为：%x\n", *(int*)&s);
    //通过函数指针调用函数，验证正确性	
    typedef void(*Function)(void);
    Function pfn;
   //遍历
    for (int i = 0; i < 6; i++)
    {
       // * ((int*)(*(int*)&sub) + i);       (int*)(*(int*)&sub) + i   虚表中 虚函数地址向后偏移 
       // (*(int*)&sub) 虚表地址              * ((int*)(*(int*)&sub) 取虚表中前4字节解引用 也就是第一个虚函数地址
        pfn = (Function)*((int*)(*(int*)&s) + i);
        pfn();
    }
 
}

int main01()
{
    test();
    return 0;

}


//2、单继承有函数覆盖(打印Sub对象的虚函数表)
struct Base
{
public:
    virtual void Function_1()
    {
        printf("Base:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Base:Function_2...\n");
    }
    virtual void Function_3()
    {
        printf("Base:Function_3...\n");
    }
};
struct Sub :Base
{
public:
    virtual void Function_1()
    {
        printf("Sub:Function_1...\n");
    }
    virtual void Function_2()
    {
        printf("Sub:Function_2...\n");
    }
    virtual void Function_6()
    {
        printf("Sub:Function_6...\n");
    }
};

void test1()
{
    Sub sub;
    typedef void(*Func)(void);
    Func pfnc;

    //Sub 中 func1 func2 把父类中 func1  func2 跟新覆盖了 
    //所以打印时 不能按照覆盖前个数打印，读取完虚表 循环还没结束出现 非法寻址问题
    //for (int i = 0; i < 6; i++)  err
    for (int i = 0; i < 4; i++)
    {
        pfnc = (Func) * ((int*)(*(int*)&sub) + i);
        pfnc();
    }
}

int main()
{
  
    test1();
    return 0;
}