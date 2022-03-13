#include"manager.h"



	//构造函数
Manager::Manager(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

	//展示个人信息
void Manager::ShowInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位名称：" << this->GetDeptName() 
		<<"\t岗位职责： 完成老板交给的任务，并下发给员工" << endl;
}

	//获取员工岗位名称
string  Manager::GetDeptName()
{
	return string("经理");
}
