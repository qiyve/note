#include<iostream>
using namespace std;

//�﷨ ��template<typename  T>
//����ģ��


//�����������κ���
void swapInt(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//�������������ͺ���
void swapDouble(double& A, double& B)
{
	double temp = A;
	A = B;
	B = temp;
}

//����ģ��
/*����һ��ģ�壬���߱���������
�����н����ŵ�T��Ҫ����T��һ��ͨ����������*/
template<typename T> 
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void test01()
{
	int a = 10;
	int b = 20;
	//swapInt(a,b);
	//���ú���ģ�彻��
	//���ַ�ʽʹ�ú���ģ��
	
	//1���Զ������Ƶ�
	//mySwap(a, b);

	//2����ʾָ������
	mySwap<int>(a, b);
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;


	/*double A = 2.1;
	double B = 3.2;
	swapDouble(A, B);
	cout << "A= " << A << endl;
	cout << "B= " << B << endl;*/
}

int main()
{
	test01();

	system("pause");
	return 0;
}