#include<stdio.h>
#include<stdlib.h>

//今天练习：
//1、定义一个unsiged char 类型，通过程序为第3、5、7位赋值, 赋值时不能
//影响到其它位原来的值.
//(使用位操作指令、比如：& | !^ << >>等)
void func()
{
	unsigned char c = 0;
	char x = 4;

	//     0000 0000 
	//Xor  0000 0100
	c = c ^ x;
	printf("%x\n", c ^ x);

	//  0001 0000
	 c += c << 2;
	printf("%x\n", c ); 
	// 0001 0100

	char y = 0x40;
	//   0100 0000
	// | 0001 0100    1010 1011
	c = c | y;
	printf("%x\n", c);

	char a = 0xab;
	c = c & a;  
	// 0000 0000
	printf("%x\n", c);
}

//2、判断某个位的值是否为1.
//(使用位操作指令、比如： & | !^ << >>等)
void  test(char c, int b)
{
	if ((c >> (8 - b)) % 2 != 0 )
	{
		printf("第%d位的值为: 1\n", b);
		
	}   
	else
	{
		printf("第%d位的值为: 0\n", b);
	}

}

//3、读取第7、6、5位的值，以十进制显示(unsigned).
//(使用位操作指令、比如： & | !^ << >>等)

int main()
{
	
	unsigned char c = 0xab;
	int a = 0;
	test(c, 1);


	printf("%x", c >> 1);

	return 0;
}
