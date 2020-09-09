/**
 * Author			:	Rakesh Malik
 * Date				:	27/10/2011
 * Subject			:	Huge Integer Class
 * Assignment no.	:	2 
 */

#include <iostream>
#include <cctype>
#include <myexception>

using namespace std;
using namespace exception;

class InvalidHugeIntFormatException:public Exception {
	public:
	InvalidHugeIntFormatException():Exception(200,"Invalid HugeInt Format Exception"){}
};

class HugeInt {
private:
	bool negative;
	string num;
	HugeInt subtract(HugeInt);
	HugeInt add(HugeInt);
public:
	HugeInt(string);
	HugeInt(long);
	HugeInt(const HugeInt&);
	HugeInt operator=(HugeInt);
	HugeInt operator=(string);
	HugeInt operator=(long);
	operator long();
	operator string();
friend  HugeInt operator+(HugeInt,HugeInt);
friend  HugeInt operator-(HugeInt,HugeInt);
friend  ostream& operator<<(ostream&,HugeInt);
friend  istream& operator>>(istream&,HugeInt&);
};
HugeInt::HugeInt(string num=(string)"0") {
	if(num.length()==0)
		throw InvalidHugeIntFormatException();
	if(num[0]=='-')
		HugeInt::negative=true;
	else
		HugeInt::negative=false;
	if(num[0]=='-'||num[0]=='+')
		num=num.substr(1);
	if(num.length()==0)
		throw InvalidHugeIntFormatException();
	for(int i=0;i<num.length();i++)
		if(!isdigit(num[i]))
			throw InvalidHugeIntFormatException();
	for(int i=0;i<num.length();i++)
		if(num[i]!='0') {
			num=num.substr(i);
			break;
		}
	HugeInt::num=num;
}
HugeInt::HugeInt(long n) {
	HugeInt::negative=false;
	HugeInt::num="";
	if(n<0) {
		HugeInt::negative=true;
		n=-n;
	}
	while(n!=0) {
		num.insert(0,1,(char)(n%10+'0'));
		n/=10;
	}
	if(HugeInt::num=="")
		HugeInt::num="0";
}
HugeInt::HugeInt(const HugeInt& x) {
	HugeInt::negative=x.negative;
	HugeInt::num=x.num;
}
HugeInt HugeInt::subtract(HugeInt x) {
	HugeInt y;
	int length=(HugeInt::num.length()>x.num.length()?HugeInt::num.length():x.num.length())+1;
	string addend=HugeInt::num;
	string augend=x.num;
	string sum="";
	for(int i=addend.length();i<length;i++)
		addend="0"+addend;
	if(HugeInt::negative==true) {
		for(int i=0;i<addend.length();i++)
			addend[i]=9-(addend[i]-'0')+'0';
		for(int c=1,i=addend.length()-1;i>=0;i--) {
			int a=addend[i]-'0';
			addend[i]=(c+a)%10+'0';
			c=(c+a)/10;
		}
	}
	for(int i=augend.length();i<length;i++)
		augend="0"+augend;
	if(x.negative==false) {
		for(int i=0;i<augend.length();i++)
			augend[i]=9-(augend[i]-'0')+'0';
		for(int c=1,i=augend.length()-1;i>=0;i--) {
			int a=augend[i]-'0';
			augend[i]=(c+a)%10+'0';
			c=(c+a)/10;
		}
	}
	for(int c=0,i=length-1;i>=0;i--) {
		int a=addend[i]-'0';
		int b=augend[i]-'0';
		sum.insert(0,1,(char)((a+b+c)%10+'0'));
		c=(a+b+c)/10;
	}
	if(sum[0]=='9') {
		y.negative=true;
		for(int i=0;i<sum.length();i++)
			sum[i]=9-(sum[i]-'0')+'0';
		for(int c=1,i=sum.length()-1;i>=0;i--) {
			int a=sum[i]-'0';
			sum[i]=(c+a)%10+'0';
			c=(c+a)/10;
		}
	}else {
		y.negative=false;
	}
	for(int i=0;i<=sum.length();i++)
		if(sum[i]!='0') {
			sum=sum.substr(i);
			break;
		}
	if(sum=="") sum="0";
	y.num=sum;
	HugeInt::negative=y.negative;
	HugeInt::num=y.num;
	return y;
}
HugeInt HugeInt::add(HugeInt x) {
	HugeInt _x=0;
	_x=_x.subtract(x);
	return HugeInt::subtract(_x);
}
HugeInt HugeInt::operator=(HugeInt x) {
	HugeInt::negative=x.negative;
	HugeInt::num=x.num;
	return *this;
}
HugeInt HugeInt::operator=(string num) {
	HugeInt x=num;
	HugeInt::negative=x.negative;
	HugeInt::num=x.num;
	return *this;
}
HugeInt HugeInt::operator=(long num) {
	HugeInt x=num;
	HugeInt::negative=x.negative;
	HugeInt::num=x.num;
	return *this;
}
HugeInt::operator long() {
	long num=0;
	for(int i=HugeInt::num.length()-1,exp=1;i>=0;i--,exp*=10)
		num+=exp*(HugeInt::num[i]-'0');
	if(HugeInt::negative)
		num=-num;
	return num;
}
HugeInt::operator string() {
	return (HugeInt::negative?"-":"")+num;
}
HugeInt operator+(HugeInt x,HugeInt y) {
	return x.add(y);
}
HugeInt operator-(HugeInt x,HugeInt y) {
	return x.subtract(y);
}
ostream& operator<<(ostream& os,HugeInt x) {
	if(x.negative==true)
		os<<"-";
	os<<x.num;
	return os;
}
istream& operator>>(istream& is,HugeInt& x) {
	string num;
	is>>num;
	HugeInt y=num;
	x.negative=y.negative;
	x.num=y.num;
	return is;
}

main() {
	HugeInt x;
	HugeInt y;
	cout<<"x=";
	try {
		cin>>x;
	}catch(InvalidHugeIntFormatException e) {
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	cout<<"x=";
	try {
		cin>>y;
	}catch(InvalidHugeIntFormatException e) {
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	cout<<"x+y="<<x+y<<endl;
	cout<<"x-y="<<x-y<<endl;
}
