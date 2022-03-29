#include"Student.h"

//Ĭ�Ϲ���
Student::Student()
{


}

//�вι���  ������ѧ�� ���� ����
Student::Student(int id, string name, string pwd)
{
	//��ʼ����
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	

}

//�˵�����
void Student::operMenu()
{
	cout << "��ӭѧ������:" << this->m_Name << "��¼��" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         1������ԤԼ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         2���鿴�ҵ�ԤԼ       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         3���鿴����ԤԼ       |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         4��ȡ��ԤԼ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         0��ע����¼           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "��ѡ�����Ĳ���" << endl;

}

//����ԤԼ
void Student::applyOrder()
{
	int date = 0;  //�����û�ѡ�������
	int interval = 0; //�����û�ѡ���ʱ���
	int room = 0;//�û�ѡ�񼸺Ż���

	cout << "��������ʱ��Ϊ��һ����!" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;


	while (true)  //ѡ���ܼ�
	{
		cin >> date;
		//�޶���СΪ1 ���Ϊ5
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ��ʱ���" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true) //ѡ�����������
	{
		cin >> interval;
		//�޶���СΪ1 ���Ϊ2
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ�Ļ���" << endl;
	cout << "1��һ�Ż���������" << vCom[0].m_MaxNum << "��" << endl;
	cout << "2�����Ż���������" << vCom[1].m_MaxNum << "��" << endl;
	cout << "3�����Ż���������" << vCom[2].m_MaxNum << "��" << endl;

	while (true) //ѡ�����
	{
		cin >> room;
		//�޶���СΪ1 ���Ϊ3
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ�,�����" << endl;

	ofstream ofs(ORDER_FILE, ios::app);//����׷�ӷ�ʽд�ļ�
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

//�鿴����ԤԼ
void Student::showMyOrder()
{


}

//�鿴����ԤԼ
void Student::showAllOrder()
{


}

//ȡ��ԤԼ
void Student::cancelOrder()
{


}