#include<iostream>
#include<string>
#include"radix36.h"
using namespace std;
/*
class radix36
{
public:
	radix36(string str)
	{
		auto beg=str.rbegin(),end=str.rend();
		while(beg!=end)
		{
			que.push(*beg);
			++beg;
		}
	}
	void operator=(radix36 &r2)
	{
		que=r2.que;	
	}
	radix36 operator+(radix36 &r2)
	{
		radix36 r1;
		//write somrthing to add them
	}
private:
	queue<char> que;
};
*/
int main()
{
	string a="103";
	string b="205";
	
	while(cin>>a)
	{
		cin>>b;
		radix36 r1(a);
		radix36 r2(b);
		radix36 r3=r1+r2;
		radix36 r4=r1-r2;
	/*
	for(char ch:a)
		cout<<ch;
	cout<<endl;
	auto beg=a.rbegin(),end=a.rend();
	while(beg!=end)
	{
		cout<<*beg;
		++beg;
	}
	*/
		cout<<r1<<"+"<<r2<<"="<<r3<<endl
		<<r1<<"-"<<r2<<"="<<r4<<endl;
	}
	return 0;
}
