#include<iostream>
using namespace std;
#include<string>


//���һ��ѧ���࣬���ԣ����� ����ѧ��
// ���Ը�������ѧ�Ÿ�ֵ��������ʾѧ����������ѧ��


//ѧ����
//class �������һ���࣬���������ŵľ���������
class Student
{
	//����Ȩ��
public://����Ȩ��

	//����
	string m_Name;//����
	int m_ID;//ѧ��

	//��Ϊ
	//��ʾ������ѧ��
	void showStudent()
	{
		cout << "������" << m_Name << "ѧ�ţ�" << m_ID << endl;
	}
};
int main()
{
	//����һ������ѧ��
	Student s1;
	//��s1���� �������Ը�ֵ
	s1.m_Name = "����";
	s1.m_ID = 1;

	//��ʾѧ����Ϣ
	s1.showStudent();

	Student s2;
	s2.m_Name = "����";
	s2.m_ID = 10;

	s2.showStudent();

	system("pause");
	return 0;
}