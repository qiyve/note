
#include <iostream>
using namespace std;

//ָ��ͺ���
void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
int main()
{
	int a = 20;
	int b = 10;
	//��ַ����  ����ǵ�ַ���ݿ�������ʵ��
	//��������޸�ʵ�ξ���ֵ���� �����޸�ʵ�ξ��õ�ַ����
	swap(&a,& b);
	
	cout << "a= " << a << endl;
	cout << "b= " << b << endl;

	system("pause");
	return 0;
}
