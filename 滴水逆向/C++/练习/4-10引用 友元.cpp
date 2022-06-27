#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*1、定义一个类，使用友元函数实现： + 、 - 、 * 、 / 、 > 、 < 、 >= 、 <=
	等运算符重载(什么情况下，一定要用友元函数 ? ) */

class Person
{
private:
	int a;
	int b;
public:

	Person(int x, int y);
	friend void Print(const Person& p);
	friend Person operator++(Person& p);
	friend Person operator--(Person& p);
	friend Person operator+(Person& x, Person& y);
	friend Person operator-(Person& x, Person& y);
	friend Person operator*(Person& x, Person& y);
	friend Person operator/(Person& x, Person& y);
	friend bool operator>(const Person& x, const Person& y);
	friend bool operator<(const Person& x, const Person& y);
	friend bool operator==(const Person& x, const Person& y);

};

Person::Person(int x, int y)
{
	this->a = x;
	this->b = y;
}
void Print(const Person& p)
{
	printf("%d\n", p.a);
	printf("%d\n", p.b);
}

Person operator++(Person& p)
{
	p.a++;
	p.b++;

	return p;
}

Person operator--(Person& p)
{
	p.a--;
	p.b--;
	return p;
}

Person operator+(Person& p, Person& y)
{
	p.a = p.a + y.a;
	p.b = p.b + y.b;
	return p;
}
Person operator-(Person& p, Person& y)
{
	p.a = p.a - y.a;
	p.b = p.b - y.b;
	return p;
}
Person operator*(Person& p, Person& y)
{
	p.a = p.a * y.a;
	p.b = p.b * y.b;
	return p;
}
Person operator/(Person& p, Person& y)
{
	p.a = p.a / y.a;
	p.b = p.b / y.b;
	return p;
}
bool operator>(const Person& p, const Person& y)
{
	if (p.a > y.a)
	{
		return true;
	}
	return false;
}
bool operator<(const Person& p, const Person& y)
{
	if (p.a < p.b)
	{
		return true;
	}
	return false;
}
bool operator==(const Person& p, const Person& y)
{
	if (p.a == y.a)
	{
		return true;
	}
	return false;
}

void test()
{
	Person p(1, 2), p2(3, 4);
	//p--;
	Print(p);
	p + p2;
	Print(p);
	p* p2;
	Print(p);
	p / p2;
	Print(p);

	p = p + p2;
	Print(p);

}
int main(int argc, char* argv[])
{
	test();

	return 0;
}
