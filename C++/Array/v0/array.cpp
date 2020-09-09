/**
 * Author			:	Rakesh Malik
 * Date				:	10/10/2011
 * Subject			:	One-Dimensional Integer Array Class
 */

#include <iostream>

using namespace std;

class Array
{
	int size;
	int *buf;
public:
	Array(int);
	Array(const Array&);
	~Array();
	int getSize();
	int& operator[](int);
	Array operator=(Array);
friend	ostream& operator<<(ostream&,Array);
};
inline Array::Array(int size)
{
	Array::size=size;
	Array::buf=new int[size];
}
inline Array::Array(const Array &a)
{
	Array::size=a.size;
	Array::buf=new int[a.size];
	for(int i=0;i<a.size;i++)
		Array::buf[i]=a.buf[i];
}
inline Array::~Array()
{
	Array::size=0;
	delete Array::buf;
}
inline int Array::getSize()
{
	return Array::size;
}
int& Array::operator[](int index)
{
	if(index>=0 && index<Array::size)
		return Array::buf[index];
	else
		throw index;
}
Array Array::operator=(Array a)
{
	Array::size=a.size;
	for(int i=0;i<a.size;i++)
		Array::buf[i]=a.buf[i];
	return *this;
}
ostream& operator<<(ostream& os,Array a)
{
	os<<"{";
	for(int i=0;i<a.size;i++)
	{
		os<<a.buf[i];
		if(i<a.size-1)
			os<<",";
	}
	os<<"}";
	return os;
}

main()
{
	Array a(10);
	a(3,4);
	cout<<a<<endl;
}
