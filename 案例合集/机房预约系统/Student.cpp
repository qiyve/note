#include"Student.h"

//默认构造
Student::Student()
{


}

//有参构造  参数：学号 姓名 密码
Student::Student(int id, string name, string pwd)
{
	//初始属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	

}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生代表:" << this->m_Name << "登录！" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         1、申请预约           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         2、查看我的预约       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         3、查看所有预约       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         4、取消预约           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         0、注销登录           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "请选择您的操作" << endl;

}

//申请预约
void Student::applyOrder()
{
	int date = 0;  //接收用户选择的日期
	int interval = 0; //接收用户选择的时间段
	int room = 0;//用户选择几号机房

	cout << "机房开放时机为周一至周!" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;


	while (true)  //选择周几
	{
		cin >> date;
		//限定最小为1 最大为5
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的时间段" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true) //选择上午或下午
	{
		cin >> interval;
		//限定最小为1 最大为2
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入申请预约的机房" << endl;
	cout << "1、一号机房容量：" << vCom[0].m_MaxNum << "人" << endl;
	cout << "2、二号机房容量：" << vCom[1].m_MaxNum << "人" << endl;
	cout << "3、三号机房容量：" << vCom[2].m_MaxNum << "人" << endl;

	while (true) //选择机房
	{
		cin >> room;
		//限定最小为1 最大为3
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功,审核中" << endl;

	ofstream ofs(ORDER_FILE, ios::app);//利用追加方式写文件
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");

}

//查看自身预约
void Student::showMyOrder()
{


}

//查看所有预约
void Student::showAllOrder()
{


}

//取消预约
void Student::cancelOrder()
{


}