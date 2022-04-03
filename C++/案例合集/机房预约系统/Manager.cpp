#include"Manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器  获取到所有文件中 学生、老师的信息
	this->initVector();

	//获取机房信息
	this->initComputer();

	//ifstream ifs;
	//ifs.open(COMPUTER_FILE, ios::in);  //读文件
	//ComputerRoom c;
	//while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	//{
	//	vCom.push_back(c); //放入容器
	//}
	//cout << "当前机房数量：" << vCom.size() << endl;
	//ifs.close(); //关闭文件
}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员:" << this->m_Name << "登录！" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1、添加账号          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2、查看账号          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3、查看机房          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4、清空预约          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0、注销登录          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";
	cout << "请选择您的操作" << endl;
}

//添加账号
void Manager::addPerson()
{
	cout << "请选择添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加教师" << endl;

	string fileName;  //操作文件名
	string tip;       //提示id号
	string errorTip;  //重复错误提示

	ofstream ofs;   //文件操作对象

	int select = 0;
	cin >> select; //接收用户选择

	while (true)
	{
		if (select == 1)
		{
			//添加的是学生
			fileName = STUDENT_FILE;
			tip = "请输入学号：";
			errorTip = "学号重复，请重新输入";
			break;
		}
		else if (select == 2) 
		{
			//添加的老师
			fileName = TEACHER_FILE;
			tip = "请输入职工编号：";
			errorTip = "职工编号重复，请重新输入";
			break;
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	//利用追加的方式 写文件
	ofs.open(fileName, ios::out | ios::app);

	int id;  //学号 /职工号
	string name; //姓名
	string pwd;  //密码

	cout << tip << endl;

	while (true)  //检测id是否重复
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) //有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close(); //关闭文件

	//调用初始化容器的接口，从新获取文件中的数据
	this->initVector();

}

//打印学生信息
void printStudent(Student& s)
{
	cout << " 学号：" << s.m_Id << " 姓名：" << s.m_Name 
		 << " 密码：" << s.m_Pwd << endl;
}

//打印教师信息
void printTeacher(Teacher& t)
{
	cout << "职工编号：" << t.m_EmpId << " 姓名：" << t.m_Name
		 << " 密码：" << t.m_Pwd << endl;
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有教师" << endl;

	int select = 0;

	cin >> select;  //接收用户选择

	if (select == 1)
	{
		//显示学生信息
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
		
	}
	else if (select == 2)
	{
		//显示教师信息
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
		
	}
	else
	{
		cout << "输入有误，请冲输入" << endl;
		system("pause");
		system("cls");
		return;
	}

	system("pause");
	system("cls");

}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId <<"号"
			<< " 容纳人数：" << (*it).m_MaxNum << "人" << endl;
	}
	system("pause");
	system("cls");
	
}

//清空机房数据
void Manager::cleanFile()
{
	cout << "是否确认清空？" << endl;
	cout << "1、是 " << endl;
	cout << "2、否 " << endl; 

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}


//初始化容器
void Manager::initVector()
{
	//确保容器清空状态
	vStu.clear();
	vTea.clear();

	//读取信息 学生
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in); //读文件

	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;  //创建对象

	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();


	//读取信息 老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Teacher t;

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "当前教师的人数为：" << vTea.size() << endl;
	ifs.close();

}

//检测重复 参数1：检测学号/职工号  参数2：检测类型
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}

//初始化机房容器
void Manager::initComputer()
{
	vCom.clear(); //确保容器为清空状态

	//ifstream ifs(COMPUTER_FILE, ios::in);
	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;

	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();

	cout << "当前机房数量：" << vCom.size() << endl;
}