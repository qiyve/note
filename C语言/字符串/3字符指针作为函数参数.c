#include <stdio.h>

int my_strlen01(char* ch)
{
	//计算字符串有效长度
	int i = 0;
	//while (ch[i] != '\0')
	//{
	//	i++;
	//}
	while (ch[i])i++;

	return i;
}
int my_strlen(const char* ch) //只读不可修改
{
	char* temp = ch; //辅助指针
	//while (*temp != '\0')temp++;
	while (*temp)temp++;
	return temp - ch; 
}

int main()
{
	char ch[] = "hello wrold";
	//printf("%s\n", ch); ch是首地址 %s依次遍历到\0
	int len= my_strlen(ch);

	printf("%d\n", len);


	system("pause");
	return 0;
}