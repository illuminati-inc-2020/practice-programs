#include <iostream>
#include <cctype>
#include "../String/string.cpp"

using namespace std;

class HugeInt
{
private:
	bool neg;
	String num;
	void setHugeInt(String);
	void normalize();
	HugeInt toTensComplement(int);
	HugeInt toSignMagnitude();
public:	
	HugeInt(String);
	void operator=(String);
	void operator=(HugeInt);
friend	HugeInt operator+(HugeInt,HugeInt);
friend	ostream& operator<<(ostream&,HugeInt);
};
void HugeInt::setHugeInt(String num)
{
	HugeInt::neg=false;
	HugeInt::num=num;
	int i=0;
	if(num.getCharAt(i)=='+')
	{
		HugeInt::neg=false;
		HugeInt::num=num.getSubString(1);
		i++;
	}
	else if(num.getCharAt(i)=='-')
	{
		HugeInt::neg=true;
		HugeInt::num=num.getSubString(1);
		i++;
	}
	for(;i<num.getLength();i++)
		if(!isdigit(num.getCharAt(i)))
		{
			HugeInt::num=(char*)"0";
			return;
		}
	HugeInt::normalize();
}
inline void HugeInt::normalize()
{
	int i;
	for(i=0;i<HugeInt::num.getLength()&&HugeInt::num.getCharAt(i)=='0';i++);
	HugeInt::num=HugeInt::num.getSubString(i);
}
HugeInt HugeInt::toTensComplement(int len)
{
	HugeInt y=*this;
	for(int i=y.num.getLength();i<len;i++)
		y.num=(char*)"0"+y.num;
	if(HugeInt::neg)
	{
		for(int i=0;i<y.num.getLength();i++)
		{
			char c=y.num.getCharAt(i);
			c=9-(c-'0')+'0';
			y.num.setCharAt(i,c);
		}
		int carry=1;
		for(int i=len-1;i>=0;i--)
		{
			int addend=y.num.getCharAt(i)-'0';
			int sum=(carry+addend)%10;
			carry=(carry+addend)/10;
			y.num.setCharAt(i,sum+'0');
		}
	}
	y.neg=false;
	return y;
}
HugeInt HugeInt::toSignMagnitude()
{
	HugeInt y=*this;
	if(y.num.getCharAt(0)=='0')
		y.neg=false;
	else
	{
		y.neg=true;
		for(int i=0;i<y.num.getLength();i++)
		{
			char c=y.num.getCharAt(i);
			c=9-(c-'0')+'0';
			y.num.setCharAt(i,c);
		}
		int carry=1;
		for(int i=y.num.getLength()-1;i>=0;i--)
		{
			int addend=y.num.getCharAt(i)-'0';
			int sum=(carry+addend)%10;
			carry=(carry+addend)/10;
			y.num.setCharAt(i,sum+'0');
		}
	}
	return y;
}
inline HugeInt::HugeInt(String num=(char*)"0")
{
	HugeInt::setHugeInt(num);
}
inline void HugeInt::operator=(String num)
{
	HugeInt::setHugeInt(num);
}
inline void HugeInt::operator=(HugeInt x)
{
	HugeInt::neg=x.neg;
	HugeInt::num=x.num;
}
ostream& operator<<(ostream &os,HugeInt x)
{
	if(x.neg)
		os<<"-";
	os<<x.num;
	return os;
}
HugeInt operator+(HugeInt x,HugeInt y)
{
	HugeInt z;
	z.num=(char*)"\0";
	int xlen=x.num.getLength();
	int ylen=y.num.getLength();
	int len=(xlen>ylen)?xlen:ylen;
	x=x.toTensComplement(len+1);
	y=y.toTensComplement(len+1);
	int carry=0;
	for(int i=0;i<len+1;i++)
	{
		int addend=x.num.getCharAt(len-i)-'0';
		int augend=y.num.getCharAt(len-i)-'0';
		int sum=(carry+addend+augend)%10;
		carry=(carry+addend+augend)/10;
		char temp[2]="\0";
		temp[0]=sum+'0';
		z.num=temp+z.num;
	}
	z=z.toSignMagnitude();
	z.normalize();
	return z;
}

main()
{
	HugeInt i=(String)(char*)"-123";
	HugeInt j=(String)(char*)"43";
	HugeInt k=i+j;
	cout<<i<<"+"<<j<<"="<<k<<endl;
}
