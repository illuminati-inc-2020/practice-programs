/**
 * Author			:	Rakesh Malik
 * Date				:	10/10/2011
 * Subject			:	One-Dimensional Integer Array Class
 * Assignment no.		:	5
 */

#include <iostream>
#include <myexception>

using namespace std;
using namespace exception;

class ArrayIndexOutOfBoundsException:public Exception {
public:
        ArrayIndexOutOfBoundsException():Exception(500,"Array Index Out of Bounds Exception"){}
};
class InvalidArrayBoundsException:public Exception {
public:
	InvalidArrayBoundsException():Exception(501,"Invalid Array Bound Exception"){}
};


class ArrayElement {
	int e;
public:
	ArrayElement(int);
	int getElement();
};
ArrayElement::ArrayElement(int e) {
	ArrayElement::e=e;
}
int ArrayElement::getElement() {
	return ArrayElement::e;
}

class Array {
	int lb,ub;
	int *buf;
public:
	Array(int,int);
	Array(const Array&);
	~Array();
	int getSize();
	int getUpperBound();
	int getLowerBound();
	void setLowerBound(int);
	void setUpperBound(int);
	int& operator[](int);
	Array operator=(Array);
friend	ostream& operator<<(ostream&,Array);
friend	istream& operator>>(istream&,Array&);
friend	Array operator,(Array,ArrayElement);
friend	Array operator,(ArrayElement,ArrayElement);
};
inline Array::Array(int lb,int ub) {
	if(lb<=ub) {
		try{
			Array::buf=new int[ub-lb+1];
			Array::ub=ub;
			Array::lb=lb;
		}catch(bad_alloc e) {
			cerr<<"Error : 'bad_alloc' exception during Array allocation"<<endl;
		}
	}
	else
		throw InvalidArrayBoundsException();
}
inline Array::Array(const Array &a) {
	try {
		Array::buf=new int[a.ub-a.lb+1];
		Array::ub=a.ub;
		Array::lb=a.lb;
		for(int i=a.lb;i<=a.ub;i++)
			Array::buf[i-a.lb]=a.buf[i-a.lb];
	}catch(bad_alloc e) {
		cerr<<"Error : 'bad_alloc' exception during Array allocation"<<endl;
	}
}
inline Array::~Array() {
	Array::lb=0;
	Array::ub=-1;
	delete Array::buf;
}
inline int Array::getSize() {
	return Array::ub-Array::lb+1;
}
inline int Array::getUpperBound() {
	return Array::ub;
}
inline int Array::getLowerBound() {
	return Array::lb;
}
void Array::setUpperBound(int ub) {
	if(ub>=Array::lb) {
		try {
			int *buf=new int[ub-Array::lb+1];
			for(int i=Array::lb;i<=ub;i++) {
				if(i<=Array::ub)
					buf[i-Array::lb]=Array::buf[i-Array::lb];
				else
					buf[i-Array::lb]=0;
			}
			delete Array::buf;
			Array::buf=buf;
			Array::ub=ub;
		}catch(bad_alloc e) {
			cerr<<"Error : 'bad_alloc' exception during Array allocation"<<endl;
		}
	}
	else
		throw InvalidArrayBoundsException();
}
void Array::setLowerBound(int lb) {
	if(lb<=Array::ub) {
		try {
			int *buf=new int[Array::ub-lb+1];
			for(int i=lb;i<=Array::ub;i++) {
				if(i>=Array::lb)
					buf[i-lb]=Array::buf[i-Array::lb];
				else
					buf[i-lb]=0;			
			}
			delete Array::buf;
			Array::buf=buf;
			Array::lb=lb;
		}catch(bad_alloc e) {
			cerr<<"Error : 'bad_alloc' exception during Array allocation"<<endl;
		}
	}
	else
		throw InvalidArrayBoundsException();
}
int& Array::operator[](int index) {
	if(index>=Array::lb && index<=Array::ub)
		return Array::buf[index-lb];
	else
		throw ArrayIndexOutOfBoundsException();
}
Array Array::operator=(Array a)
{
	for(int i=0;i<=a.ub-a.lb && i<=Array::ub-Array::lb;i++)
		Array::buf[i]=a.buf[i];
	return *this;
}
ostream& operator<<(ostream& os,Array a)
{
	os<<"{";
	for(int i=0;i<=a.ub-a.lb;i++)
	{
		os<<a.buf[i];
		if(i<a.ub-a.lb)
			os<<",";
	}
	os<<"}";
	return os;
}
istream& operator>>(istream& is,Array& a)
{
	for(int i=a.lb;i<=a.ub;i++)
		is>>a.buf[i-a.lb];
	return is;
}
Array operator,(Array a,ArrayElement e)
{
	Array b(0,a.ub-a.lb+1);
	for(int i=0;i<=a.ub-a.lb;i++)
		b.buf[i]=a.buf[i];
	b.buf[a.ub-a.lb+1]=e.getElement();
	return b;
}
Array operator,(ArrayElement e0,ArrayElement e1)
{
	Array b(0,1);
	b.buf[0]=e0.getElement();
	b.buf[1]=e1.getElement();
	return b;
}

main()
{
	int lb,ub;
	cout<<"Enter Lower Bound : ";
	cin>>lb;
	cout<<"Enter Upper Bound : ";
	cin>>ub;
	try {
		Array a(lb,ub);
		for(int i=lb;i<=ub;i++) {
			cout<<"a["<<i<<"] = ";
			cin>>a[i];
		}
		cout<<a<<endl;
		a.setUpperBound(ub+5);
		cout<<a<<endl;
		a.setLowerBound(lb+2);
		cout<<a<<endl;
		a=((ArrayElement)997,998,999);
		cout<<a<<endl;
	}catch(InvalidArrayBoundsException e) {
		cout<<"Error "<<e.getErrorNumber()<<" : "<<e.getMessage()<<endl;
	}
	
}
