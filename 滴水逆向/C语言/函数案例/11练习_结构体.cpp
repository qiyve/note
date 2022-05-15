#include<stdio.h>
#include<string.h>

//练习：
//1、定义一个结构体Monster，能够存储怪的各种信息(至少有一个成员是结构体类型)。
//2、声明一个Monster类型的数组，长度为10.
//3、编写一个函数，为第二题中的数组赋值.
//4、编写一个函数，能够通过怪物ID，打印当前这个怪物的所有信息.

typedef struct SS
{
	int ID;
	int Lv;
	int HP;

}S;

typedef struct Monster
{
	char name[10];
	S s;

}Mod;

Monster arr[10];

void get_Monster()
{
	arr[0].s.ID = 1;
	arr[0].s.HP = 1000;
	arr[0].s.Lv = 50;
	strcpy(arr[0].name, "牛头");

	arr[1].s.ID = 2;
	arr[1].s.HP = 16000;
	arr[1].s.Lv = 60;
	strcpy(arr[1].name, "马面");
}

void Print(Monster arr[], int id)
{
	for (int i = 0; i < 2; i++)
	{
		if (arr[i].s.ID == id)
		{
			printf("怪物编号：%d 怪名：%s 等级：%d 生命：%d\n", arr[i].s.ID, arr[i].name, arr[i].s.Lv, arr[i].s.HP);
		}
	}
}

int main()
{

	get_Monster();
	Print(arr, 2);

	return 0;
}
