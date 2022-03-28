#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"Student.h"
#include"Manager.h"
#include"Teacher.h"

//��¼����  ����1 �������ļ���   ����2�������������
void LoginIn(string fileName, int type)
{
	//����ָ�� ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)
	{
		cout << "���������ѧ��:" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ�����:" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;  //���ļ��ж�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd;  //���ļ��л�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
		/*	cout << fId << endl;
			cout << fName << endl;
			cout << fPwd << endl;
			cout << endl*/;

			//���û��������Ϣ���Ա�
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ�" << endl;

				system("pause");
				system("cls");
				person = new Student(id, name, pwd); 

				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
	}
	else if (type == 3)
	{
		//����Ա�����֤
	}

	cout << "��֤��¼ʧ��" << endl;
	system("pause");
	system("cls");

	return;
}

int main()
{
	int select = 0;//���ڽ����û���ѡ��

	while (true)
	{
		cout << "=================== ��ӭ�������ǲ��ͻ���ԤԼϵͳ ================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t-------------------------------\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         1��ѧ������          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         2����    ʦ          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         3���� �� Ա          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|         0����    ��          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t-------------------------------\n";
		cout << "����������ѡ��" << endl;

		cin >> select; //�����û�����

		switch (select) //�����û�����ʵ�ֲ�ͬ�ӿ�
		{
		case 1:  //ѧ�����
			LoginIn(STEDENT_FILE, 1);
			break;
		case 2:  //��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:  //�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
			
		}
		
	}









	system("pause");
	return 0;
}
