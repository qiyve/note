#include<iostream>
using namespace std;

//   004010CC | E8 4DFFFFFF    | call callingconvention.40101E        
int __stdcall Add1(int a, int b, int c)
{
	return a + b + c;
}

//004010DC | E8 24FFFFFF       | call callingconvention.401005                   |
int __cdecl Add2(int a, int b)
{
	return a + b;
}

int __fastcall Plus(int a,int b,int c,int d,int e)
{
	int t = Add1(a, b, c);
	int s = Add2(d, e);
	int Sum = Add2(t, s);
	return Sum;
}

int main()
{
	int s = Plus(1, 3, 4, 6, 7);
	cout << s;

	return 0;
}