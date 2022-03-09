#include<iostream>
using namespace std;
#include<fstream> //包含头文件
#include<string>

//文本文件 读文件

void test01()
{

	// 1. 包含头文件   #include<fstream>

	// 2. 创建流对象   ifstream ifs;
	ifstream ifs;

	//  3. 打开文件 并判断文件是否打开成功       ifs.open("文件路径“,  打开方式)
	ifs.open("写文件.txt", ios::in);

	if (!ifs.is_open()) //判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}

 //  4. 读数据          四种方式读取
  
	//第一种
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}

	//第二种
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf, sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

    //第三种
	//string buf;

	//while (getline(ifs, buf))
	//{
	//	cout << buf << endl;
	//}

	//第四种
	char c;
	while( (c=ifs.get()) !=EOF)
	{
		cout << c;
	}

 //  5. 关闭文件       ifs.close()；
	ifs.close();
}


int main()
{

	test01();

	system("pause");
	return 0;
}