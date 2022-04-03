#include"workerManager.h"


//构造函数
WorkerManager::WorkerManager()
{

	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	if (!ifs.is_open())
	{
		//初始化属性
		
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;

		ifs.close();//关闭文件
		return;
	}
	//2. 文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空

		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;

		ifs.close();//关闭文件
		return;
	}

	//3、当文件存在，并且记录数据
	int num = this->get_EmpNum();
    //cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num; // 更新成员属性

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据，存到数组中
	init_Emp();


}

//菜单功能实现
//显示菜单
void WorkerManager::Show_Menu()
{

	cout << "**************************************" << endl;
	cout << "*******  欢迎使用职工管理系统!  ******" << endl;
	cout << "***********0、退出管理程序 ***********" << endl;
	cout << "***********1、增加职工信息 ***********" << endl;
	cout << "***********2、显示职工信息 ***********" << endl;
	cout << "***********3、删除离职职工 ***********" << endl;
	cout << "***********4、修改职工信息 ***********" << endl;
	cout << "***********5、查找职工信息 ***********" << endl;
	cout << "***********6、按照编号排序 ***********" << endl;
	cout << "***********7、清空所有文档 ***********" << endl;
	cout << "**************************************" << endl;

	cout << endl;
}

//退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;

	system("pause");//请按任意键继续

	exit(0);
}

//添加功能函数
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量:" << endl;

	int addNum = 0;//保存如用输入数量
	cin >> addNum;

	if (addNum > 0)//判断是否有效输入
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数 = 原来记录的人数 + 新增人数

		//开辟空间
		Worker** newSpace= new Worker * [newSize];

		//将原来的空间下数据，拷贝到新空间下
		if (this->m_EmpArray!= NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择


			cout << "请输入第 " << i + 1 << " 个新职工编号" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工的岗位 " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boos(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		
		//释放原有空间
		delete[]this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//跟新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;

		//保存职工信息
		this->Save();
	}
	else
	{    
		cout << "输入数据有误" << endl;
	}

	//按任意键后， 清屏回到上级目录
	system("pause");
	system("cls");

}

//保存文件
void WorkerManager:: Save()
{
	ofstream ofs; //创建流对象
	ofs.open(FILENAME, ios::out);//打开文件

	//输入内容
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << " " << endl;
	}

	ofs.close();//关闭文件
}


//统计文件中人数
int WorkerManager:: get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件    读文件

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs; 
	ifs.open(FILENAME, ios::in);//打开文件 读文件

		int id;
		string name;
		int dId;

		int index = 0;

		//根据部门id 创建不同的对象
		while (ifs>>id && ifs>>name && ifs>>dId)
		{
			Worker* worker = NULL;

			if (dId == 1)//普通员工
			{
				worker = new Employee(id, name, dId);
			}
			else if (dId == 2)	//经理
			{
				worker = new Manager(id, name, dId);
			}
			else//老板
			{
				worker = new Boos(id, name, dId);
			}
			//存放在数组中
			this->m_EmpArray[index] = worker;
			index++;
			
		}
		
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//按任意键继续 清屏
	system("pause");
	system("cls");

}

//删除职工
void WorkerManager::Del_Emp()
{
	//判断文件是否存在
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除职工
		cout << "请输入您要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
	
		int index = this->IsExist(id);

		if (index != -1)//说明职工存在，并且要删掉 index位置上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			cout << "删除成功" << endl;
			this->m_EmpNum--;//更新纪录人数
			this->Save();//同步到文件中
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	//按任意键继续  并且清屏
	system("pause");
	system("cls");

}


//判断职工是否存在
int  WorkerManager::IsExist(int id)
{
	int index = -1;//默认不存在

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工  并退出循环
			index = i;
			break;
		}
	}

	return index;
}

//修改职工
void WorkerManager::Mod_Emp()
{
	//先判断文件是否存在
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号修改职工信息
		cout << "请输入您要修改的职工编号" << endl;
		int id;//保存用户输入
		cin >> id;

		//判断职工是否存在

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工

			delete this->m_EmpArray[ret];//先释放原有数据

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到 ：" << id << "号职工，请输入新职工编号" << endl;
			cin >> newId;

			cout << "请输入要修改的姓名" << endl;
			cin >> newName;

			cout << "请输入新的岗位" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;

			cin >> dSelect;

			Worker* worker = NULL;

			switch (dSelect)
			{
			case 1:  //普通员工
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:  //经理
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:  //老板
				worker = new Boos(newId, newName, dSelect);
				break;

			default:
				break;
			}

			//跟新数据 到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;

			//保存到文件中
			this->Save();

		}
		else
		{
			cout << "修改失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");//清屏

}

//查找职工
void WorkerManager::Find_Emp()
{
	//先判断文件是否存在
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
    }
	else
	{
		//提示用户有两种查找方式

		cout << "请选择您要查找的方式" << endl;
		cout << "1、通过职工编号查找" << endl;
		cout << "2、通过职工姓名查找" << endl;
		
		int select = 0;//用户选择
		cin >> select;

		if (select == 1)//按职工编号查找
		{
			int id;
			cout << "请输入查找的职工编号" << endl;//提示用户
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				 //找到职工
				cout << "查找成功，该职工信息如下：" << endl;
				this->m_EmpArray[ret]->ShowInfo();//调用展示信息函数
			}
			else
			{
				cout << "查找失败，未找到该职工" << endl;
			}
		}
		//按姓名查找
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的职工姓名" << endl;
			cin >> name;

			//加入判断是否查找到的标志
			bool flag = false;//默认未找到职工
			
			for (int i = 0; i < m_EmpNum; i++)
			{
				//判断是否有该姓名的职工
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为："
						<<this->m_EmpArray[i]->m_Id
						<<"号的信息如下"<< endl;
				
					flag = true;

					//调用显示信息接口
					this->m_EmpArray[i]->ShowInfo();
					
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "未找到该姓名的职工" << endl;
			}
		}
		else 
		{
			cout << "输入有误请重新输入" << endl;
		}
	}
	

	system("pause");
	system("cls");//清屏
}

//职工排序
void WorkerManager::Sort_Emp()
{
	//先判断文件是否存在
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或数据为空" << endl;

		system("pause");//按任意键继续 并清屏
		system("cls");
	}
	else
	{
		//提示用户有两种排序方法
		cout << "请选择排序的方式" << endl;
		cout << "1、按职工编号升序" << endl;
		cout << "2、按职工编号降序" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOMax = i;//声明最小值 或 最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
			   if (select == 1)//升序
			   {
				
					if (this->m_EmpArray[minOMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						//如果认定的最小值下标 min0Max > j 下标  更新最小值下标
						minOMax = j;
					}
			   }
			   else //降序
			   {
				   if (this->m_EmpArray[minOMax]->m_Id < this->m_EmpArray[j]->m_Id)
				   {
					   //如果认定的最大值下标 min0Max < j 下标  更新最大值下标
					   minOMax = j;
				   }
			   }
			}

			/*判断一开始认定的 最小值或最大值 是不是计算的 最小值或最大值
			 如果不是交换数据*/
			if (i != minOMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOMax];
				this->m_EmpArray[minOMax] = temp;
			}
	    }
	}
	cout << "排序成功,排序后的结果为: " << endl;
	this->Save();//排序后结果保存到文件中

	this->Show_Emp();//调用接口显示成员
}

//清空文件
void WorkerManager::Cleam_File()
{
	//提示用户是否确认清空文件
	cout << "请确认文件是否清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、退出" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
	   //清空文件
		ofstream ofs(FILENAME, ios::trunc);  //删除文件并重新创建
		ofs.close();//关闭文件

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray == NULL;
			}

			//删除堆区数组指针
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
	
		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");

}

//析构函数
WorkerManager::~WorkerManager()
{
	  //判断数组是否为空 不为空把他释放掉  堆区内存手动释放
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}
