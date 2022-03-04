#include<iostream>
using namespace std;
#include<string>

//继承中的对象模型

//公共继承
class Baese
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1:public Baese
{
public:

	int m_D;
};

void test01()
{
	cout << "sizeof Son1 = " << sizeof(Son1) << endl;
}
int main()
{
	
	test01();

	system("pause");
	return 0;
}