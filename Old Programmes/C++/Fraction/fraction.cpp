/**
 * Author			:	Rakesh Malik
 * Date				:	11/10/2011
 * Subject			:	Fraction Class
 * Assignment no.		:	1
 */

#include <iostream>
#include <myexception>

using namespace std;
using namespace exception;

class DivideByZeroException:public Exception {
public:
	DivideByZeroException():Exception(0,"Divide By Zero Exception"){}
};
class ZeroDenominatorException:public Exception {
public:
	ZeroDenominatorException():Exception(100,"Zero Denominator Exception"){}
};

int gcd(int x,int y) {
	if(x==0 || y==0)
		return 1;
	x=(x<0)?-x:x;
	y=(y<0)?-y:y;
	while(x!=y)
		if(x>y)
			x-=y;
		else
			y-=x;
	return x;
}

class Fraction {
	int n;
	int d;
	void adjustFraction();
public:
	Fraction(int,int);
	int getNumerator();
	int getDenominator();
	Fraction operator+();
	Fraction operator-();
	Fraction operator++();
	Fraction operator++(int);
	Fraction operator--();
	Fraction operator--(int);
	Fraction operator+=(Fraction);
	Fraction operator-=(Fraction);
	Fraction operator*=(Fraction);
	Fraction operator/=(Fraction);
	bool operator==(Fraction);
	bool operator!=(Fraction);
	bool operator>(Fraction);
	bool operator>=(Fraction);
	bool operator<(Fraction);
	bool operator<=(Fraction);
	operator double();
friend	Fraction operator+(Fraction,Fraction);
friend	Fraction operator-(Fraction,Fraction);
friend	Fraction operator*(Fraction,Fraction);
friend	Fraction operator/(Fraction,Fraction);
friend	ostream& operator<<(ostream&,Fraction);
friend	istream& operator>>(istream&,Fraction&);
};
void Fraction::adjustFraction() {
	int x=gcd(Fraction::n,Fraction::d);
	Fraction::n/=x;
	Fraction::d/=x;
	if(Fraction::d<0) {
		Fraction::n*=-1;
		Fraction::d*=-1;
	}
}
Fraction::Fraction(int n=0,int d=1) {
	if(d!=0) {
		Fraction::n=n;
		Fraction::d=d;
		Fraction::adjustFraction();
	}else {
		throw ZeroDenominatorException();
	}
}
inline int Fraction::getNumerator() {
	 return Fraction::n;
}
inline int Fraction::getDenominator() {
	 return Fraction::d;
}
Fraction Fraction::operator+() {
	return *this;
}
Fraction Fraction::operator-() {
	Fraction f;
	f.n=-Fraction::n;
	f.d=Fraction::d;
	return f;
}
Fraction Fraction::operator++() {
	Fraction::n+=Fraction::d;
	return *this;
}
Fraction Fraction::operator++(int dummy) {
	Fraction f=*this;
	Fraction::n+=Fraction::d;
	return f;
}
Fraction Fraction::operator--() {
	Fraction::n-=Fraction::d;
	return *this;
}
Fraction Fraction::operator--(int dummy) {
	Fraction f=*this;
	Fraction::n+=Fraction::d;
	return f;
}
Fraction Fraction::operator+=(Fraction f2) {
	Fraction f;
	f.n=Fraction::n*f2.d+f2.n*Fraction::d;
	f.d=Fraction::d*f2.d;
	f.adjustFraction();
	Fraction::n=f.n;
	Fraction::d=f.d;
	return f;
}
Fraction Fraction::operator-=(Fraction f2) {
	Fraction f;
	f.n=Fraction::n*f2.d-f2.n*Fraction::d;
	f.d=Fraction::d*f2.d;
	f.adjustFraction();
	Fraction::n=f.n;
	Fraction::d=f.d;
	return f;
}
Fraction Fraction::operator*=(Fraction f2) {
	Fraction f;
	f.n=Fraction::n*f2.n;
	f.d=Fraction::d*f2.d;
	f.adjustFraction();
	Fraction::n=f.n;
	Fraction::d=f.d;
	return f;
}
Fraction Fraction::operator/=(Fraction f2) {
	if(f2.n!=0) {
		Fraction f;
		f.n=Fraction::n*f2.d;
		f.d=Fraction::d*f2.n;
		f.adjustFraction();
		Fraction::n=f.n;
		Fraction::d=f.d;
		return f;
	}else {
		throw DivideByZeroException();
	}
}
bool Fraction::operator==(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d==0);
}
bool Fraction::operator!=(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d!=0);
}
bool Fraction::operator>(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d>0);
}
bool Fraction::operator>=(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d>=0);
}
bool Fraction::operator<(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d<0);
}
bool Fraction::operator<=(Fraction f) {
	return (Fraction::n*f.d-f.n*Fraction::d<=0);
}
Fraction::operator double() {
	return (double)Fraction::n/(double)Fraction::d;
}
Fraction operator+(Fraction f1,Fraction f2) {
	Fraction f;
	f.n=f1.n*f2.d+f2.n*f1.d;
	f.d=f1.d*f2.d;
	f.adjustFraction();
	return f;
}
Fraction operator-(Fraction f1,Fraction f2) {
	Fraction f;
	f.n=f1.n*f2.d-f2.n*f1.d;
	f.d=f1.d*f2.d;
	f.adjustFraction();
	return f;
}
Fraction operator*(Fraction f1,Fraction f2) {
	Fraction f;
	f.n=f1.n*f2.n;
	f.d=f1.d*f2.d;
	f.adjustFraction();
	return f;
}
Fraction operator/(Fraction f1,Fraction f2) {
	if(f2.n!=0) {
		Fraction f;
		f.n=f1.n*f2.d;
		f.d=f1.d*f2.n;
		f.adjustFraction();
		return f;
	}else {
		throw DivideByZeroException();
	}
}
ostream& operator<<(ostream &out,Fraction f) {
	out<<f.n<<"/"<<f.d;
	return out;
}
istream& operator>>(istream &in,Fraction &f) {
	char dummy;
	in>>f.n>>dummy>>f.d;
	if(f.d==0)
		throw ZeroDenominatorException();
	f.adjustFraction();
	return in;
}

main() {
	Fraction f1,f2;
	cout<<"f1 = ";
	try {
		cin>>f1;
	}catch(ZeroDenominatorException e) {
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	cout<<"f2 = ";
	try {
		cin>>f2;
	}catch(ZeroDenominatorException e) {
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	cout<<"f1 = "<<f1<<" = "<<(int)f1<<" = "<<(double)f1<<endl;
	cout<<"f2 = "<<f2<<" = "<<(int)f2<<" = "<<(double)f2<<endl;
	cout<<"f1+f2 = "<<f1+f2<<endl;	
	cout<<"f1-f2 = "<<f1-f2<<endl;	
	cout<<"f1*f2 = "<<f1*f2<<endl;	
	try {
		cout<<"f1/f2 = "<<f1/f2<<endl;	
	}catch(DivideByZeroException e) {
		cout<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
}
