#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct DateInfo
{
	int year;
	int month;
	int day;

	DateInfo(int a, int b, int c)
	{
		this->year = a;
		this->month = b;
		this->day = c;
	}
	DateInfo()
	{
		this->year = 2015;
		this->month = 4;
		this->day = 2;
	}

	void SetDay(int day)
	{
		this->day = day;
	}

	int GetDay()
	{
		return this->day;
	}

	void SetYear(int year)
	{
		this->year;
	}

	int GetYear()
	{
		return this->year;
	}

	void SetMonth(int month)
	{
		this->month;
	}
	int GetMonth()
	{
		return this->month;
	}
};

struct TimeInfo:DateInfo
{
	int hour;
	int minute;
	int second;

	void SetHour(int hour)
	{
		this->hour = hour;
	}
	void SetMinute(int minute)
	{
		this->minute = minute;
	}
	void SetSecond(int second)
	{
		this->second = second;
	}

	int GetHour()
	{
		return this->hour;
	}
	int GetMinute()
	{
		return this->minute;
	}
	int GetSecond()
	{
		return this->second;
	}
};

void test()
{
	TimeInfo time;
	time.SetHour(10);
	time.SetMinute(20);
	time.SetSecond(30);

	TimeInfo* p1 = &time; //子类指针
	DateInfo* p2 = &time; //父类指针

	printf("子类访问：%d年 %d月 %d日 %d时 %d分 %d秒 \n", p1->GetYear(), p1->GetMonth(),
		p1->GetDay(), p1->GetHour(), p1->GetMinute(), p1->GetSecond());

	printf("父类访问：%d年 %d月 %d日 \n", p2->GetYear(), p2->GetMonth(), p2->GetDay());

}

int main02()
{
	test();

	return 0;
}

struct MyString
{
	char* arr;

	MyString(int n)
	{
		arr = (char*)malloc(n);
	}
	MyString()
	{
		arr = (char*)malloc(1024);
	}

	~MyString()
	{
		printf("释放成功\n");
		free(arr);
		arr = NULL;
	}

	void SetString(char str[])
	{
		strcpy(this->arr, str);
	}
	void PrintString()
	{
		printf("%s\n", this->arr);
	}

	void AppendString(char str[])
	{
		strcat(this->arr, str);//将字符串追加到目标尾部
	}

	int Size()
	{
		return strlen(arr);
	}

};



void Test()
{
	char arr1[] = "hello";
	char arr2[] = "world";

	MyString MyStr;

	MyString* p = &MyStr;

	p->SetString(arr1);
	p->PrintString();
	printf("Size:%d\n", p->Size());

	p->AppendString(arr2);
	p->PrintString();
	printf("Size:%d\n", p->Size());

}

int main()
{
	Test();

	return 0;
}