#ifndef RADIX36_H
#define RADIX36_H

#include<string>
#include<vector>
#include<iostream>

class radix36_element
{
public:
	radix36_element(char ch)
	{
		init(ch);
		carry=0;	
	}
	radix36_element(char ch,int c)
	{
		init(ch);
		carry=c;
	}

	bool if_the_initialization_is_failed() const;
//to see if the value_for_calcualting is equal to -1, that is, the ch for initialization is not the characters in the range of radix36_element.      
	
	void operator=(const radix36_element &);
	friend radix36_element& operator+(const radix36_element &,const int &);
	friend radix36_element& operator+(const radix36_element &,const radix36_element &);
	friend radix36_element& operator-(const radix36_element &,const radix36_element &);  
	friend radix36_element& operator*(const radix36_element &,const radix36_element &);  
	//friend radix36_element& operator/(const radix36_element &,const radix36_element &);
	friend std::ostream& operator<<(std::ostream &,const radix36_element &);
	//friend std::istream& operator>>(std::isttream &,const radix36_element &);

	void clear_the_carry();
	char get_the_element() const;
	int get_the_value() const;
	int get_the_carry() const;
private:
	void init(char ch)//use a char-type value to initialize this and get the corresponding by the way.
	{
		char element=ch;
                if(((int)ch-(int)'0')>=0&&((int)ch-(int)'0'<=9))
                        value_for_calculating=(int)ch-(int)'0';
                else if(((int)ch-(int)'a')>=0&&((int)ch-(int)'a'<=25))
                        value_for_calculating=((int)ch-(int)'a')+10;
                else   
                        value_for_calculating=-1;//-1 denote a failed initialization    
	}
	char element;
	int value_for_calculating;
	int carry;//用来存储加法及乘法产生的进位数。
};

class radix36
{
public:
	radix36()
	{
		positive=true;
	}
	radix36(std::string str)
	{
		init(str);
		positive=true;
	}
	radix36(std::string str,bool if_positive)
	{
		init(str);
		positive=if_positive;
	}
	
	friend std::ostream& operator<<(std::ostream &,const radix36 &);
	friend radix36& operator+(const radix36 &,const radix36 &);
	//friend radix36& operator*(const radix36 &,const radix36 &);
	//friend radix36& operator-(const radix36 &,const radix36 &);
	//friend radix36& operator/(const radix36 &,const radix36 &);
	void operator=(radix36 &);

	void add_the_element(radix36_element &);	
	inline int get_vec_size()const;
	inline radix36_element get_char_in_vec(int)const;//take the subscript as the parameter and return the corresponding element.
private:
	void init(std::string str)
	{
		auto beg=str.rbegin(),end=str.rend();//We should store the string in the que in the reverse order.
		while(beg!=end)
		{
			radix36_element re(*beg);
			vec.push_back(re);
			++beg;
		}
	}
	std::vector<radix36_element> vec;//For the convenience of the operation later, the lower digit is at front
	bool positive;
};

#endif
