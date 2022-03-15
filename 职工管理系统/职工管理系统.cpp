#include<iostream>
using namespace std;
#include"WorkerManager.h" 

#include"worker.h"//职工抽象类
#include"employee.h"//普通职工类
#include"manager.h"//经理类
#include"boos.h"//老板类


int main()
{

	//实例化管理者对象
	WorkerManager wm;

	//创建用户输入的变量
	int choice = 0;

	//利用 while 循环展示菜单
	while (true)
	{
		//调用展示菜单的成员函数
		wm.Show_Menu();

		cout << "请输入您的选择: " << endl;//提示用户输入

		cin >> choice; //接收用户输入内容

		//利用 switch 语句显示不同功能
		switch (choice)
		{
		case 0://退出系统
			wm.exitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break; 
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://排序职工
			wm.Sort_Emp();
			break;
		case 7://清空文档
			wm.Cleam_File();
			break;
		defaule:
			system("cls"); //清屏
			break;
		}

	}



	system("pause");
	return 0;
}