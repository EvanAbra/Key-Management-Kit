#include<iostream>
#include<string>
#include<queue>
#include"radix36.h"

using namespace std;

//the define for the function appeared in the class radix36_element
bool radix36_element::if_the_initialization_is_failed() const
{
	if(value_for_calculating==-1)
		return false;
	else
		return true;
}

void radix36_element::operator=(const radix36_element &re)
{
	element=re.element;
	value_for_calculating=re.value_for_calculating;
	carry=re.carry;
}

radix36_element operator+(const radix36_element &re1, const int &carry)
{
	int result=re1.get_the_value()+carry;
	int ca=(int)(result/36)+re1.get_the_carry();
	char ele;
	if(result>35)
		result=result-36;

	if(result>=0&&result<=9)
		ele=(char)((int)'0'+result);
	else 
		ele=(char)((int)'a'+(result-10));

	radix36_element re(ele,ca);
	return re;
}

radix36_element operator+(const radix36_element &re1, const radix36_element &re2)
{
	int result=re1.get_the_value()+re2.get_the_value();
	int ca=(int)(result/36)+re1.get_the_carry()+re2.get_the_carry();//the value of carry;
	char ele;//the character corresponding to the value;
	if(result>35)
		result=result-36;
	
	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else
	{
		ele=(char)((int)'a'+(result-10));
	}
	
	radix36_element re(ele,ca);
	return re;
}

radix36_element operator*(const radix36_element &re1, const radix36_element &re2)
{
	int result=re1.get_the_value()*re2.get_the_value();
	int ca=(int)(result/36);
	char ele;
	while(result>35)
		result=result-36;
	
	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else
	{
		ele=(char)((int)'a'+(result-10));
	}

	radix36_element re(ele,ca);
	return re;
}

radix36_element operator-(const radix36_element &re1, const radix36_element &re2)
{
	int result=re1.get_the_value()-re2.get_the_value();
	int ca=(int)(result/36);//used to store the carry
	char ele;
	if(result<0)
		result=result+36;

	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else
	{
		ele=(char)((int)'a'+(result-10));
	}

	radix36_element re(ele,ca);
	return re;
}

ostream& operator<<(ostream &os,const radix36_element &re)
{
	os<<re.get_the_element();
	return os;
}

char radix36_element::get_the_element() const
{
	return element;
}

int radix36_element::get_the_value() const
{
	return value_for_calculating;
}

int radix36_element::get_the_carry() const
{
	return carry;
}

void radix36_element::clear_the_carry()
{
	carry=0;
}
//the define for the function appeared in the class radix36
ostream& operator<<(ostream &os,const radix36 &r)
{
	for(int i=r.get_vec_size()-1;i>=0;i--)
	{
		os<<r.get_char_in_vec(i);
	}
	return os;
}

radix36 operator+(const radix36 &r1,const radix36 &r2)
{
	radix36 r;
	int smaller_size=r1.get_vec_size();
	int bigger_size=r2.get_vec_size();
	if(smaller_size>bigger_size)
		smaller_size^=bigger_size^=smaller_size^=bigger_size;//exchange the contents in the smaller_size and bigger_size.
	int carry=0;
	for(int i=0;i<smaller_size;i++)
	{
		radix36_element nre=r1.get_char_in_vec(i)+r2.get_char_in_vec(i)+carry;
		carry=nre.get_the_carry();
		nre.clear_the_carry();
		r.add_the_element(nre);	
	}
	for(int i=smaller_size;i<bigger_size;i++)
	{
		if(r1.get_vec_size()>r2.get_vec_size())
		{
			radix36_element nre=r1.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
		else
		{
			radix36_element nre=r2.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
	}	
	if(carry!=0)
	{
		radix36_element nre('1');
		r.add_the_element(nre);
	}
	
	return r;
}

void radix36::add_the_element(radix36_element &re)
{
	vec.push_back(re);
}

void radix36::operator=(radix36 &r)
{
	vec=r.vec;
}

inline int radix36::get_vec_size() const
{
	return vec.size();
}

inline radix36_element radix36::get_char_in_vec(int subscript) const
{
	return vec.at(subscript);
}
