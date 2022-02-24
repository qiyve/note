#include<iostream>
using namespace std;
#include<string>    //string 头文件
#define MAX   1000  //最大值1000
//设计联系人结构体
struct person
{
	// 姓名
	string m_Name;
	// 性别  1 男   2女
	int m_Sex;
	//年龄
	int m_Age;
	//联系电话
	string m_Phone;
	//家庭地址
	string m_Address;
};

//设计通讯录的结构体
struct Addressbooks
{
	//通讯录中保存的联系人数组
	struct person personArray[MAX];

	//通讯录中当前记录联系人个数
	int m_Size;
};
//1、添加联系人
void addPerson(Addressbooks* ads)
{
	//判断通讯录是否已满，如果满了就不在添加
	if (ads->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
	    //添加具体联系人
		
		//姓名
		string name;
		cout << "请输入姓名" << endl;
		cin >> name;
		ads->personArray[ads->m_Size].m_Name = name;

		//性别
		cout << "请输入性别" << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;
		int sex = 0;

		while (true)
		{
			//如果输入的是 1 或者 2 可以退出循环，因为输入的是正确值
			//如果输入有误，重新输入
 			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				ads->personArray[ads->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}
		//年龄
		cout << "请输入年龄" << endl;
		int age=0;
		cin >> age;
		ads->personArray[ads->m_Size].m_Age = age;

		//电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		ads->personArray[ads->m_Size].m_Phone = phone;

		//地址
		cout << "请输入家庭地址 " << endl;
		string address;
		cin >> address;
		ads->personArray[ads->m_Size].m_Address = address;
		
		//更新通讯录人数
		ads->m_Size++;

		cout << "添加成功" << endl;

	   
		system("pause"); //请按任意键继续
		system("cls");  // 清屏操作
	} 
}
//2、显示所有联系人
void showperson(Addressbooks* ads)
{
	//判断当前通讯录中没有人员，就提示记录为空
	// 如果人数大于 0 显示通讯录中信息
	if (ads->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{        
		for (int i = 0; i < ads->m_Size; i++)
		{
			cout << "姓名：" << ads->personArray[i].m_Name << "\t";
			                  //利用三木运算符 
			cout << "性别：" <<(ads->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
			cout << "年龄：" << ads->personArray[i].m_Age << "\t";
			cout << "电话号码" << ads->personArray[i].m_Phone << "\t";
			cout << "家庭地址" << ads->personArray[i].m_Address << endl;
		}
	}
	system("pause");// 请按任意键继续
	system("cls");//  清屏

}
//检测联系人是否存在 如果存在，返还这个联系人在通讯录中的位置。不存在返回 - 1
//参数1： 通讯录  参数2： 对比性名
int isExist(Addressbooks* ads, string name)
{
	for (int i = 0; i < ads->m_Size; i++)
	{
		//找到用户输入的姓名了
		if (ads->personArray[i].m_Name == name)
		{
			return i;//找到了，返回这个人在数组中下标编号
		}
	}
		return -1;//如果遍历结束都没找到，返回-1
}
//3、删除指定联系人
void deleteperson(Addressbooks* ads)
{
	cout << "请输入联系人的姓名：" << endl;

	string name;
	cin >> name;

	// ret==-1  未查到  
	//ret!=-1 查到了
	int ret=isExist(ads, name);

	if (ret != -1)
	{
      //查找到进行删除操作
		for (int i = ret; i < ads->m_Size; i++)
		{
			//数据前移
			ads->personArray[i] = ads->personArray[i + 1];
		}
		ads->m_Size--;//更新通讯录人数 
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");//请按任意键继续
	system("cls");//清屏
}

//4、查找指定联系人信息
void findperson(Addressbooks* ads)
{
	cout << "请输入您要查找的联系人：" << endl;
	string name;
	cin >> name;

	//判断联系人是否存在  存在显示数据   不存在提示查无此人
	int ret = isExist(ads, name);

	if (ret != -1)//ret!=-1 查到了
	{
		//找到联系人 并打印数据
		cout << "姓名：" << ads->personArray[ret].m_Name << "\t";
		cout << "性别：" << ads->personArray[ret].m_Sex << "\t";
		cout << "年龄：" << ads->personArray[ret].m_Age << "\t";
		cout << "电话号码：" << ads->personArray[ret].m_Phone << "\t";
		cout << "家庭地址：" << ads->personArray[ret].m_Address << endl;
	}
	else// ret==-1  未查到  
	{
		cout << "查无此人" << endl;
	}

	system("pause");//按任意键继续
	system("cls");//  清屏
}

//5、修改指定联系人
void modifyperson(Addressbooks* ads)
{
	cout << "请输入您要修改的联系人：" << endl;
	string name;
	cin >> name;
	int ret = isExist(ads, name);

	//判断用户输入的联系人是否存在 存在进行修改信息  不存在提示查无此人
	if (ret!=-1) // 查到了
	{
		//修改联系人信息

		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		ads->personArray[ret].m_Name = name;

		//性别
		cout << "请输入性别：" << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				//输入正确 修改信息  并退出循环
				ads->personArray[ret].m_Sex = sex;
				break;
			}
			else
			{
				cout << "输入有误，请重新输入：" << endl;
			}
		}

		//年龄 
		int age= 0;
		cout << "请输入年龄：" << endl;
		cin >> age;
		ads->personArray[ret].m_Age = age;
	 
		// 联系电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		ads->personArray[ret].m_Phone = phone;

		// 家庭地址
		cout << "请输入家庭地址：" << endl;
		string address;
		cin >> address;
		ads->personArray[ret].m_Address = address;

	}
	else
	{   // ret== -1 未查到
		cout << "查无此人" << endl;
	}

	system("pause"); //按任意键继续
	system("cls");  //清屏

}

//6、清空联系人
void cleanperson(Addressbooks*ads)
{
	//将通讯录所有联系人信息清除掉，只要将通讯录记录的联系人数量置为0，
	ads->m_Size = 0;
	cout << "通讯录以清空" << endl;

	system("pause");//按任意键继续
	system("cls");  //清屏
}

//菜单界面
void showMenu()
{
	cout << "***********************" << endl;
	cout << "*****1、添加联系人*****" << endl;
	cout << "*****2、显示联系人*****" << endl;
	cout << "*****3、删除联系人*****" << endl;
	cout << "*****4、查找联系人*****" << endl;
	cout << "*****5、修改联系人*****" << endl;
	cout << "*****6、清空联系人*****" << endl;
	cout << "*****0、退出通讯录*****" << endl;
	cout << "***********************" << endl;
}

int main()
{
	//创建通讯录结构体变量
	Addressbooks ads;
	//初始化通讯录中当前人员个数
	ads.m_Size = 0;

	int select = 0; //创建用户选择输入的变量
	//创建一个循环 
	while (true)
	{
		//菜单调用
		showMenu();
		
		cin >> select; //接收用户输入内容

		switch (select)
		{
		case 1://添加联系人
			addPerson(&ads);//利用地址传递 修饰实参
			break;

		case 2://显示联系人
			showperson(&ads);
			break;

		case 3://删除联系人
			deleteperson(&ads);
			break;

		case 4://查找联系人
			findperson(&ads);
			break;

		case 5://修改联系人
			modifyperson(&ads);
			break;

		case 6://清空联系人
			cleanperson(&ads);
			break;

		case 0://退出通讯录
			cout << "欢迎下次使用" << endl;

			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}





