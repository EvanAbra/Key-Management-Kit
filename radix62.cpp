#include<iostream>
#include<string>
#include<queue>
#include"radix62.h"

using namespace std;

//the define for the function appeared in the class radix36_element
bool radix62_element::if_the_initialization_is_failed() const
{
	if(value_for_calculating==-1)
		return false;
	else
		return true;
}

void radix62_element::operator=(const radix62_element &re)
{
	element=re.element;
	value_for_calculating=re.value_for_calculating;
	carry=re.carry;
}

bool radix62_element::operator>(const radix62_element &re)
{
	if(value_for_calculating>re.value_for_calculating)
		return true;
	else
		return false;
}

bool radix62_element::operator<(const radix62_element &re)
{
	if(value_for_calculating<re.value_for_calculating)
		return true;
	else
		return false;
}

bool radix62_element::operator==(const radix62_element &re)
{
	if(value_for_calculating==re.value_for_calculating)
		return true;
	else
		return false;
}

bool radix62_element::operator>=(const radix62_element &re)
{
	if(value_for_calculating>=re.value_for_calculating)
		return true;
	else
		return false;
}

bool radix62_element::operator<=(const radix62_element &re)
{
	if(value_for_calculating<=re.value_for_calculating)
		return true;
	else
		return false;
}

radix62_element operator+(const radix62_element &re1, const int &carry)
{
	int result=re1.get_the_value()+carry;
	int ca;
	if(result<0)
		ca=-1;
	else
		ca=(int)(result/62)+re1.get_the_carry();
	char ele;
	if(result<0)
		result=result+62;
	else if(result>61)
		result=result-36;

	if(result>=0&&result<=9)
		ele=(char)((int)'0'+result);
	else if(result>=10&&result<=35)
		ele=(char)((int)'a'+(result-10));
	else
		ele=(char)((int)'A'+(result-36));

	radix62_element re(ele,ca);
	return re;
}

radix62_element operator+(const radix62_element &re1, const radix62_element &re2)
{
	int result=re1.get_the_value()+re2.get_the_value();
	int ca=(int)(result/62)+re1.get_the_carry()+re2.get_the_carry();//the value of carry;
	char ele;//the character corresponding to the value;
	if(result>61)
		result=result-62;
	
	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else if(result>=10&&result<=35)
	{
		ele=(char)((int)'a'+(result-10));
	}
	else
		ele=(char)((int)'A'+(result-36));

	radix62_element re(ele,ca);
	return re;
}

radix62_element operator*(const radix62_element &re1, const radix62_element &re2)
{
	int result=re1.get_the_value()*re2.get_the_value();
	int ca=(int)(result/62);
	char ele;
	while(result>61)
		result=result-62;
	
	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else if(result>=10&&result<=35)
	{
		ele=(char)((int)'a'+(result-10));
	}
	else
		ele=(char)((int)'A'+(result-36));

	radix62_element re(ele,ca);
	return re;
}

radix62_element operator-(const radix62_element &re1, const radix62_element &re2)
{
	int result=re1.get_the_value()-re2.get_the_value();
	int ca;//used to store the carry
	if(result<0)
		ca=-1;
	else 
		ca=0;
	char ele;
	if(result<0)
		result=result+62;

	//计算出对应的字符
	if(result>=0&&result<=9)
	{
		ele=(char)((int)'0'+result);
	}
	else if(result>=10&&result<=35)
	{
		ele=(char)((int)'a'+(result-10));
	}
	else 
		ele=(char)((int)'A'+(result-36));

	radix62_element re(ele,ca);
	return re;
}

ostream& operator<<(ostream &os,const radix62_element &re)
{
	os<<re.get_the_element();
	return os;
}

char radix62_element::get_the_element() const
{
	return element;
}

int radix62_element::get_the_value() const
{
	return value_for_calculating;
}

int radix62_element::get_the_carry() const
{
	return carry;
}

void radix62_element::clear_the_carry()
{
	carry=0;
}
//the define for the function appeared in the class radix36
ostream& operator<<(ostream &os,const radix62 &r)
{
	if(!r.if_positive())
		os<<'-';
	for(int i=r.get_vec_size()-1;i>=0;i--)
	{
		os<<r.get_char_in_vec(i);
	}
	return os;
}

radix62 operator+(const radix62 &r1,const radix62 &r2)
{
	radix62 r;
	int smaller_size=r1.get_vec_size();
	int bigger_size=r2.get_vec_size();
	if(smaller_size>bigger_size)
		smaller_size^=bigger_size^=smaller_size^=bigger_size;//exchange the contents in the smaller_size and bigger_size.
	int carry=0;
	for(int i=0;i<smaller_size;i++)
	{
		radix62_element nre=r1.get_char_in_vec(i)+r2.get_char_in_vec(i)+carry;
		carry=nre.get_the_carry();
		nre.clear_the_carry();
		r.add_the_element(nre);	
	}
	for(int i=smaller_size;i<bigger_size;i++)
	{
		if(r1.get_vec_size()>r2.get_vec_size())
		{
			radix62_element nre=r1.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
		else
		{
			radix62_element nre=r2.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
	}	
	if(carry!=0)
	{
		radix62_element nre('1');
		r.add_the_element(nre);
	}
	
	return r;
}

radix62 operator-(const radix62 &r1,const radix62 &r2)
{
	radix62 r;
	bool po=(r1>=r2);
	r.set_positive(po);
	int carry=0;
	if(po==true)//po==true means that r1-r2>=0
	{
		for(int i=0;i<r2.get_vec_size();i++)
		{
			radix62_element nre=r1.get_char_in_vec(i)-r2.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
		for(int i=r2.get_vec_size();i<r1.get_vec_size();i++)
		{
			radix62_element nre=r1.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
	}
	else
	{
		for(int i=0;i<r1.get_vec_size();i++)
		{
			radix62_element nre=r2.get_char_in_vec(i)-r1.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}
		for(int i=r1.get_vec_size();i<r2.get_vec_size();i++)
		{
			radix62_element nre=r2.get_char_in_vec(i)+carry;
			carry=nre.get_the_carry();
			nre.clear_the_carry();
			r.add_the_element(nre);
		}	
	}
	r.clear_the_redundant_zeros();
	return r;
}

radix62 operator*(const radix62 &r1,const radix62 &r2)
{
	radix62 r;
	for(int i=0;i<r1.get_vec_size();i++)
		for(int j=0;j<r2.get_vec_size();j++)
		{
			radix62_element nre=r1.get_char_in_vec(i)*r2.get_char_in_vec(j);
			if(r.get_vec_size()<(i+j+1))
				r.add_the_element(nre);
			else
				r.change_element_in_vec(r.get_char_in_vec(i+j)+nre,i+j+1);
		}
	
	//handle the carry which is left in the every element in r
	int carry=0;
	for(int i=0;i<r.get_vec_size();i++)
	{	
		radix62_element nre=r.get_char_in_vec(i)+carry;
		carry=nre.get_the_carry();
		nre.clear_the_carry();
		r.change_element_in_vec(nre,i+1);
	}
	if(carry!=0)
	{
		char ele;	
		
		//计算出对应字符
		if(carry>=0&&carry<=9)
		{
			ele=(char)((int)'0'+carry);
		}
		else if(carry>=10&&carry<=35)
		{
			ele=(char)((int)'a'+(carry-10));
		}
		else 
			ele=(char)((int)'A'+(carry-36));

		radix62_element nre(ele);
		r.add_the_element(nre);	
	}

	return r;
}

bool operator>(const radix62 &r1,const radix62 &r2)
{
	if(r1.get_vec_size()>r2.get_vec_size())
		return true;
	else if(r1.get_vec_size()<r2.get_vec_size())
		return false;
	for(int i=r1.get_vec_size();i>0;i--)
	{
		if(r1.get_char_in_vec(i-1)>r2.get_char_in_vec(i-1))
			return true;
		else if(r1.get_char_in_vec(i-1)<r2.get_char_in_vec(i-1))
			return false;
	}	
	return false;//only happen when r1==r2
}

bool operator<(const radix62 &r1,const radix62 &r2)
{
	if(r1.get_vec_size()<r2.get_vec_size())
		return true;
	else if(r1.get_vec_size()>r2.get_vec_size())
		return false;
	for(int i=r1.get_vec_size();i>0;i--)
	{
		if(r1.get_char_in_vec(i-1)<r2.get_char_in_vec(i-1))
			return true;
		else if(r1.get_char_in_vec(i-1)>r2.get_char_in_vec(i-1))
			return false;
	}
	return false;//only happen when r1==r2
}

bool operator==(const radix62 &r1,const radix62 &r2)
{
	if(r1.get_vec_size()<r2.get_vec_size())
		return false;
	else if(r1.get_vec_size()>r2.get_vec_size())
		return false;
	for(int i=r1.get_vec_size();i>0;i--)
	{
		if(r1.get_char_in_vec(i-1)<r2.get_char_in_vec(i-1))
			return false;
		else if(r1.get_char_in_vec(i-1)>r2.get_char_in_vec(i-1))
			return false;
	}
	return true;//only happen when r1==r2
}

bool operator<=(const radix62 &r1,const radix62 &r2)
{
	if(r1.get_vec_size()<r2.get_vec_size())
		return true;
	else if(r1.get_vec_size()>r2.get_vec_size())
		return false;
	for(int i=r1.get_vec_size();i>0;i--)
	{
		if(r1.get_char_in_vec(i-1)<r2.get_char_in_vec(i-1))
			return true;
		else if(r1.get_char_in_vec(i-1)>r2.get_char_in_vec(i-1))
			return false;
	}
	return true;//only happen when r1==r2
}

bool operator>=(const radix62 &r1,const radix62 &r2)
{
	if(r1.get_vec_size()>r2.get_vec_size())
		return true;
	else if(r1.get_vec_size()<r2.get_vec_size())
		return false;
	for(int i=r1.get_vec_size();i>0;i--)
	{
		if(r1.get_char_in_vec(i-1)>r2.get_char_in_vec(i-1))
			return true;
		else if(r1.get_char_in_vec(i-1)<r2.get_char_in_vec(i-1))
			return false;
	}
	return true;//only happen when r1==r2
}

void radix62::clear_the_redundant_zeros()
{
	auto highest_digit=vec.end()-1;//the iterator point to the highest digit of the number
	
	//>1 while not =1 because we want to remain one zero when there are all zero.
	while(*highest_digit=='0'&&vec.size()>1)	
	{
		vec.erase(highest_digit);
		highest_digit--;
	}
}

void radix62::add_the_element(radix62_element &re)
{
	vec.push_back(re);
}

void radix62::change_element_in_vec(const radix62_element &r,const int &num)
{
	if(vec.size()>=num)
		vec.at(num-1)=r;
}//The number is counted from one

bool radix62::if_positive() const
{
	return positive;
}

void radix62::set_positive(const bool &flag)
{
	positive=flag;
}

void radix62::operator=(const radix62 &r)
{
	vec=r.vec;
}

inline int radix62::get_vec_size() const
{
	return vec.size();
}

inline radix62_element radix62::get_char_in_vec(int subscript) const
{
	return vec.at(subscript);
}
