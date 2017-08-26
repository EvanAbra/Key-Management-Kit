#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"radix62.h"
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
void help()//print information of instructions
{
	cout<<"To get the key, enter 1. Enter 2 to store the key"<<endl;
}

int main()
{
	fstream in("Key.txt",ios::in|ios::out|ios::app);
	vector<string> info;
	vector<radix62> key;
	if(in.is_open())
	{
		int counter=0;
		cout<<"info\b\b\b\b\t\t\tkey"<<endl;
		while(!in.eof())
		{
			string a;
			in>>a;
			info.push_back(a);
			in>>a;
			radix62 r(a);
			key.push_back(r);
			cout<<info[counter];
			for(int i=0;i<info[counter].size();i++)
				cout<<'\b';
			cout<<"\t\t\t"<<key[counter]<<endl;
			counter++;
		}
		in.close();
	}
	else
		cout<<"failed to open the file."<<endl;
	
	int mode=0;//indicate what to do	
	help();
	while(cin>>mode)
	{
		if(mode==1)
		{
			cout<<"please enter the corresponding information of the key"<<endl;
			string a;
			cin>>a;
			int cnt=-1;//used to store the subscript of the info
			for(int i=0;i<info.size();i++)
			{
				if(a==info[i]){
					cnt=i;
					break;
				}
			}
			if(cnt==-1)
				cout<<"No information to match."<<endl;
			else
			{
				string secondary_key;
				cout<<"Enter the secondary_key please."<<endl;
				cin>>secondary_key;
				radix62 seco_key(secondary_key);
				cout<<key[cnt]-seco_key<<endl;
			}
		}
		else if(mode==2)
		{
			ofstream out("Key.txt",ios::app);
			cout<<"please enter the information, the key and the secondary key in order."<<endl;
			string a,b,c;
			cin>>a>>b>>c;
			info.push_back(a);
			out<<a<<" ";
			radix62 rb(b);
			radix62 rc(c);
			out<<rb+rc<<endl;
			key.push_back(rb+rc);
			out.close(); 
		}
		else
			cout<<"Invalid mode indicator."<<endl;
	}
	return 0;
}
