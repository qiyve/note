
#include"boos.h"



	//构造函数
Boos::Boos(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = did;
}

	//显示个人信息
void Boos::ShowInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位名称：" << this->GetDeptName()
		<< "\t岗位职责： 管理公司所有事务" << endl;
 }

	//获取岗位名称
string Boos::GetDeptName()
{
	return string("总裁");
}

