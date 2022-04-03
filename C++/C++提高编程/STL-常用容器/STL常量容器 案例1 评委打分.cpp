#include<iostream>
using namespace std;
#include<deque>
#include<vector>
#include<string>
#include<algorithm>//标准算法头文件
#include<ctime>  //机数种子包含 ctime 头文件

//STL 案例 评委打分
//有五名选手：选手ABCDE,10个评委分别对每个选手打分，去除最高分，去除评委中最低分，取平局分

//选手类
class Person
{
public:

	Person(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}

	string m_Name; //姓名
	int m_Score;  //平均分
};

//创建选手
void createPerson(vector<Person>&v)
{

	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		string name = "选手";
		name += nameSeed[i];

		int score = 0;

		Person p(name, score);

		//将创建的Person对象，放入到容器
		v.push_back(p);
	}
}

//打分
void setScore(vector<Person>&v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//将评委的分数 放入deque容器中
		deque<int>d;
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60;//60~100  随机数利用 rand（）

			d.push_back(score);//放入容器中
		}
		
		/*测试打分
		cout << "选手：" << it->m_Name << "得分：" << endl;
		for (deque<int>::const_iterator dit = d.begin(); dit != d.end(); dit++)
		{
			cout << *dit << " ";
		}
		cout << endl;*/

		//排序
		sort(d.begin(), d.end());
          
		d.pop_back(); //去除最高分
		d.pop_front();//去除最低分

		//取平均分
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit; //累加每个评委分数
		}
		int avg = sum / d.size();

		//将平均分赋值给选手
		it->m_Score = avg;

	}
}

//显示平均分
void showScore(vector<Person>&v)
{
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手：" << (*it).m_Name << " 平均分：" << (*it).m_Score << endl;
	}
}

void test01()
{
	//添加随机数种子
	srand((unsigned int)time(NULL));

	//1、创建5名选手
	vector<Person>v;
	createPerson(v);

	//测试
	/*for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "姓名：" << (*it).m_Name << " 分数：" << (*it).m_Score << endl;
	}*/

	//2、给5名选手打分
	setScore(v);

	//3、显示最后得分
	showScore(v);
}

int main()
{
	test01();
	

	system("pause");
	return 0;
}