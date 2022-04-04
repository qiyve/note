#include<stdio.h>
//宏定义常量
#define PI 3.14159

//圆的面积 s = pi * r * r
//圆的周长 l = 2 * pi * r

int main()
{
	//常量PI
	//cosnt 数据类型 常量名 = 值
	//const float pi = 3.14159;

	float r = 2.f;

	float s = PI * r * r;
	float l = 2 * PI * r;

	//占位符 %f 表示输出一个浮点型 float  默认保留六位小数  会四舍五入
	printf("圆的面积：%.2f\n", s);
	printf("圆的周长：%.2f\n", l);

	return 0;
}