#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
#include<ctime>

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));

	//创建管理类对象
	SpeechManager sm;

	//测试创建12名选手
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "编号：" << it->first 
	//		<< " 姓名：" << it->second.m_Name 
	//		<< " 分数：" << it->second.m_Score[1] << endl;
 //   }
	
	int choice = 0; //保存用户输入

	
	while (true)
	{
		sm.show_Menu(); //调用菜单

		cout << "请输入您的选择" << endl;
		cin >> choice;//接收用户输入

		switch (choice)
		{
		case 1:     //开始比赛
			sm.startSpeech();
			break;
		case 2:     //查看往届记录
			sm.showRecord();
			break;
		case 3:     //清空记录
			sm.clearRecord();
			break;
		case 0:     //退出程序
			sm.exitSystem();
			break;

		default:
			system("cls");   //清屏
			break;
		}
	}
	




	system("pause");
	return 0;
}