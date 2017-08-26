#ifndef RADIX62_H
#define RADIX62_H

#include<string>
#include<vector>
#include<iostream>

class radix62_element
{
public:
	radix62_element(char ch)
	{
		init(ch);
		carry=0;	
	}
	radix62_element(char ch,int c)
	{
		init(ch);
		carry=c;
	}

	bool if_the_initialization_is_failed() const;
//to see if the value_for_calcualting is equal to -1, that is, the ch for initialization is not the characters in the range of radix36_element.      
	
	void operator=(const radix62_element &);
	friend radix62_element operator+(const radix62_element &,const int &);
	friend radix62_element operator+(const radix62_element &,const radix62_element &);
	friend radix62_element operator-(const radix62_element &,const radix62_element &);  
	friend radix62_element operator*(const radix62_element &,const radix62_element &);  
	bool operator>(const radix62_element &);
	bool operator<(const radix62_element &);
	bool operator==(const radix62_element &);
	bool operator>=(const radix62_element &);
	bool operator<=(const radix62_element &);
	//friend radix36_element& operator/(const radix36_element &,const radix36_element &);
	friend std::ostream& operator<<(std::ostream &,const radix62_element &);
	//friend std::istream& operator>>(std::isttream &,const radix36_element &);

	void clear_the_carry();
	char get_the_element() const;
	int get_the_value() const;
	int get_the_carry() const;
private:
	void init(char ch)//use a char-type value to initialize this and get the corresponding by the way.
	{
		element=ch;
                if(((int)ch-(int)'0')>=0&&((int)ch-(int)'0'<=9))
                        value_for_calculating=(int)ch-(int)'0';
                else if(((int)ch-(int)'a')>=0&&((int)ch-(int)'a'<=25))
                        value_for_calculating=((int)ch-(int)'a')+10;
		else if(((int)ch-(int)'A')>=0&&((int)ch-(int)'A'<=25))
			value_for_calculating=((int)ch-(int)'A')+36;
                else   
                        value_for_calculating=-1;//-1 denote a failed initialization    
	}
	char element;
	int value_for_calculating;
	int carry;//用来存储加法及乘法产生的进位数。
};

class radix62
{
public:
	radix62()
	{
		positive=true;
	}
	radix62(std::string str)
	{
		init(str);
		positive=true;
	}
	radix62(std::string str,bool if_positive)
	{
		init(str);
		positive=if_positive;
	}
	
	friend std::ostream& operator<<(std::ostream &,const radix62 &);
	friend radix62 operator+(const radix62 &,const radix62 &);
	friend radix62 operator*(const radix62 &,const radix62 &);
	friend radix62 operator-(const radix62 &,const radix62 &);
	//friend radix36& operator/(const radix36 &,const radix36 &);
	friend bool operator>(const radix62 &,const radix62 &);
	friend bool operator<(const radix62 &,const radix62 &);
	friend bool operator==(const radix62 &,const radix62 &);
	friend bool operator<=(const radix62 &,const radix62 &);
	friend bool operator>=(const radix62 &,const radix62 &);
	void operator=(const radix62 &);

	void clear_the_redundant_zeros();//clear the redundant zeros in the front of the sentence
	void add_the_element(radix62_element &);	
	void change_element_in_vec(const radix62_element &,const int &);//rewrite the value of the pointed element in the vector. The number is counted from the lower digit.The number is counted from one.
	bool if_positive() const;
	void set_positive(const bool &);
	inline int get_vec_size() const;
	inline radix62_element get_char_in_vec(int)const;//take the subscript as the parameter and return the corresponding element.
private:
	void init(std::string str)
	{
		//count the number of the redundant zeros in the front of the sentence
		int num_of_zeros=0;
		if(str[0]=='0')
		{
			auto beg=str.begin(),end=str.end();
			while(beg!=end&&*beg=='0')
			{
				num_of_zeros++;
				beg++;
			}
			if(beg==end)
				num_of_zeros--;//if str only contains zeros, then remain one zero.
		}
		
		//store the string in the vector in the reverse order for the convenience of calculating.
		//and skip the redundant zeros.
		for(int i=str.size()-1;i>=num_of_zeros;i--)
		{
			radix62_element re(str[i]);
			vec.push_back(re);
		}
	}
	std::vector<radix62_element> vec;//For the convenience of the operation later, the lower digit is at front
	bool positive;
};

#endif
