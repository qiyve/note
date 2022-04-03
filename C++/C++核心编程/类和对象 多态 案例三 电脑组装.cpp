#include<iostream>
using namespace std;
#include<string>

// 案例三 电脑组装

//抽象不同零件的类
//抽象CPU类
class CPU
{
public:
    //抽象计算函数
	virtual void calculate() = 0;
};

//抽象显卡类
class VideoCard
{
public:
	//抽象显示函数
	virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
	//抽象存储函数
	virtual void storage() = 0;
};

//创建计算机类
class Computer
{
public:
	Computer(CPU *cpu,VideoCard *vc,Memory *mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}

	//提供工作函数
	void word()
	{
		//让零件工作起来，调用接口
		m_cpu->calculate();

		m_vc->display();

		m_mem->storage();
	}
	//提供析构函数 释放3个电脑零件
	~Computer()
	{
		//释放CPU零件
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
        }

		//释放显卡零件
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}

		//释放内存条零件
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}

private:
	CPU * m_cpu;//CPU零件指针
	VideoCard * m_vc;//显卡零件指针
	Memory * m_mem;//内存条零件指针
};

//具体厂商
//Intel 厂商
class IntelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel的CPU正在计算" << endl;
	}
};

class IntelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel的显卡正在显示" << endl;
	}
};

class IntelMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条正在存储" << endl;
	}

};

//Lenovo厂商
class LenovoCPU : public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo的CPU正在计算" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡正在显示" << endl;
	}
};

class LenovoMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo的内存条正在存储" << endl;
	}

};

void test01()
{
	//第一台电脑零件
	CPU* intelCpu = new IntelCPU;
	VideoCard* intelvc = new IntelVideoCard;
	Memory* intelmem = new IntelMemory;

	//创建第一台电脑
	cout << "第一台开始工作" << endl;
	Computer* computer1 = new Computer(intelCpu, intelvc, intelmem);
	computer1->word();
	delete computer1;//堆区内存手动开辟手动释放

    //第二台电脑 组装
	cout << "--————————————--" << endl;
	cout << "第二台开始工作" << endl;
	Computer* computer2 = new Computer(new LenovoCPU,new LenovoVideoCard,new LenovoMemory);
	computer2->word();
	delete computer2;

	//第三台电脑组装
	cout << "--————————————--" << endl;
	cout << "第三台开始工作" << endl;
	Computer* computer3 = new Computer(new IntelCPU, new LenovoVideoCard, new IntelMemory);
	computer3->word();
	delete computer3;

}
int main()
{

	test01();

	system("pause");
	return 0;
}