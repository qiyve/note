#include<stdio.h>

//本节练习：
//1、char类型占几字节？char * 类型占几字节？int*****占几字节？
//2、char** arr[10] 占多少个字节？
//3、自定义结构体如下：
struct Student
{
	int x;
	int y;
};

void test()
{
	//char x;
	//char* y;
	//int***** z;

	//x = 10;   //  1 
	//y = (char*)20;  //4
	//z = (int*****)30; // 4
	//char** arr[10]; //40

	//Student**** s;
	//s = (Student****)100;
	//s++;		//s的值是多少？	    104
	//s = s + 2;		//s的值是多少？	112
	//s = s - 3;		//s的值是多少？	100

	//第二步：
/*	Student**** s1;
	Student**** s2;
	int x;
	s1 = (Student****)200;
	s2 = (Student****)100;
	x = s1 - s2;*/		//x的值是多少？	x = 100 / 4

	//Student* s;
	//s = (Student*)100;   
	////带 * 类型的变量，++ 或者 -- 新增(减少)的数量是去掉一个 * 后变量的宽度
	//s++;		//s的值是多少？	       108  结构体字节   
	//s = s + 2; //s的值是多少？	       124   s = s + N*(去掉一个*后类型的宽度）
	//s = s - 3;		//s的值是多少？	   100 


	Student* s1;
	Student* s2;
	int x;
	s1 = (Student*)200;  
	s2 = (Student*)100;
	x = s1 - s2;		//x的值是多少？	 100 / 8

	printf("%d", x);

	
}

int main()
{
	test();
 
	return 0;
}
