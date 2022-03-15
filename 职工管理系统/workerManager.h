#pragma once        //防止头文件重复包含
#include<iostream>   //包含输入输出流 头文件
using namespace std; //标准的命名空间
#include"Worker.h"   //职工抽象类
#include"employee.h" //普通员工类
#include"manager.h"  //经理类
#include"boos.h"     //老板

#include<fstream>    //读写头文件
#define FILENAME "empFile.txt"


//管理类
class WorkerManager
{
public:

	//构造函数
	WorkerManager();

	//展示菜单
	void Show_Menu();

	//退出系统
	void exitSystem();

    //记录职工人数
	int m_EmpNum;

	//添加功能函数
	void Add_Emp();

	//职工数组指针
	Worker** m_EmpArray;

	//保存文件
	void Save();

	//标志文件是否为空
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();  

	//删除职工
	void Del_Emp();

    //判断职工是否存在
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//职工排序
	void Sort_Emp();

	//清空文件
	void Cleam_File();

	//析构函数
	~WorkerManager();
};