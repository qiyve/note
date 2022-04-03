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

	//cout << "请输入申请预约的机房" << endl;
	//cout << "1、一号机房容量：" << vCom[0].m_MaxNum << "人" << endl;
	//cout << "2、二号机房容量：" << vCom[1].m_MaxNum << "人" << endl;
	//cout << "3、三号机房容量：" << vCom[2].m_MaxNum << "人" << endl;
	cout << "请选择机房" << endl;
	for (int i = 0;i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
	}

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
	ofs << "date:" << date << " ";              //日期
	ofs << "interval:" << interval << " ";      //时间段
	ofs << "stuId:" << this->m_Id << " ";       //学生id
	ofs << "stuName:" << this->m_Name << " ";   //学生姓名
	ofs << "roomId:" << room << " ";            //机房编号
	ofs << "status:" << 1 << endl;              //1：审核中状态

	ofs.close();

	::system("pause");
	system("cls");

}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	//of.updateOrder();

	if (of.m_Size == 0)
	{
		cout << "无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{ 
		//string  转  int
		//string  利用 .c_str  转  const char *
		//利用 atoi( const char *) 转int
	
		//cout <<"学生编号："<<of.m_orderData[i]["stuId"] << endl;

		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))//找到自身预约
		{
			cout << "预约的日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号:" << of.m_orderData[i]["roomId"];

			string status = " 状态:";
			//1、审核中  2、预约成功 -1、预约失败  0、取消预约
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败，审核未通过";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of; //创建对象

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	//遍历数据
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";  //拼接显示第几条预约


		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房号：" << of.m_orderData[i]["roomId"];
		
		//1、审核中  2、预约成功 -1、预约失败  0、取消预约
		string status = " 状态：";

		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
	    }

		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约通过";
		}	

		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}	

		else
		{
			status += "预约已取消";
		}

		cout << status << endl;
	
	}

	system("pause");
	system("cls");

}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "预约记录为空!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	vector<int>v; //存放在最大容器的下标编号
	int index = 1; 
	
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断自身学号 
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			//在筛选状态  审核中或预约成功
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ <<"、" << endl; //提示用户第几条记录
				cout << "预约的日期：周" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房号：" << of.m_orderData[i]["roomId"];

				string status = " 状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	//开始取消预约
	cout << "请输入取消的记录,0代表返回" << endl;
	int select = 0;
	
	while (true)
	{
		cin >> select;
	
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//下标 = 用户传入的 select-1   改为0 取消预约
				of.m_orderData[v[select - 1]]["status"] = "0";

				of.updateOrder(); //更新文件

				cout << "已取消预约！" << endl;
				break;
			}

		}
		
		cout << "输入有误请重新输入" << endl;
	}

	system("pause");
	system("cls");
}