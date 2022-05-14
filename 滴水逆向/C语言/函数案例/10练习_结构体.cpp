#include<stdio.h>

//练习：
//1、定义一个结构体Gamer用来存储一个游戏中的角色的信息，包括血值、等级、坐标等信息
//要求：
//(1) 具体包含哪些信息自由设计
//(2) 但这些包含的类型中，必须要有一个成员是结构体类型
//3、定义一个函数，用来显示这个结构体变量的所有成员信息.

struct Coordinates //坐标
{
	float x;
	float y;
	float z;
};

struct Gamer
{
	int HP;   //生命
	float CD; //技能冷却
	int MP;   //蓝条
	Coordinates C; //坐标

};

void ShowGamer(Gamer g);
//2、定义一个函数，用来给这个结构体变量赋值.
void func(Gamer g)
{
	g.HP = 100;
	g.MP = 100;
	g.CD = 5.0f;
	g.C.x = 0.0f;
	g.C.y = 0.0f;
	g.C.z = 0.0f;

	ShowGamer(g);
}

//显示信息
void ShowGamer(Gamer g)
{
	printf("生命值：%d 法力值：%d 技能冷却：%0.2f \n ", g.HP, g.MP, g.CD);
	printf("当前坐标：X：%0.2f Y:%0.2f Z：%0.2f \n", g.C.x, g.C.y, g.C.z);
}


int main()
{
	Gamer g;
	func(g);

	return 0;
}
