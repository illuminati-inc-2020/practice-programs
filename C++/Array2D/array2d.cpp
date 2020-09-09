/**
 * Author			:	Rakesh Malik
 * Date				:	13/09/2011
 * Class			:	Two-Dimentional Integer Array
 */

#include <iostream>

using namespace std;

class Array
{
	int dummy;
	int size;
	int *buf;
public:
	Array(int);
	Array(const Array&);
	~Array();
	int getSize();
	int& operator[](int);
	Array operator=(Array);
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
		return dummy;
}
Array Array::operator=(Array a)
{
	Array::size=a.size;
	for(int i=0;i<a.size;i++)
		Array::buf[i]=a.buf[i];
	return *this;
}

class Array2D
{
	Array *dummy;
	int m;			// number of rows
	int n;			// number of columns
	Array **buf;
public:
	Array2D(int,int);
	Array2D(const Array2D&);
	~Array2D();
	int getRows();
	int getColumns();
	Array& operator[](int);
};
inline Array2D::Array2D(int m,int n)
{
	Array2D::dummy=new Array(m);
	Array2D::m=m;
	Array2D::n=n;
	Array2D::buf=new Array*[n];
	for(int i=0;i<n;i++)
		Array2D::buf[i]=new Array(m);
}
inline Array2D::Array2D(const Array2D& a)
{
	Array2D::dummy=new Array(m);
	Array2D::m=m;
	Array2D::n=n;
	Array2D::buf=new Array*[n];
	for(int i=0;i<n;i++)
	{
		Array2D::buf[i]=new Array(m);
		for(int j=0;j<m;j++)
			Array2D::buf[i][j]=a.buf[i][j];
	}
}
inline Array2D::~Array2D()
{
	delete Array2D::dummy;
	for(int i=0;i<Array2D::n;i++)
		delete Array2D::buf[i];
	delete Array2D::buf;
	Array2D::m=0;
	Array2D::n=0;
}
inline int Array2D::getRows()
{
	return Array2D::n;
}
inline int Array2D::getColumns()
{
	return Array2D::m;
}
inline Array& Array2D::operator[](int index)
{
	if(index>=0 && index<Array2D::n)
		return *Array2D::buf[index];
	else
		return *Array2D::dummy;
}

main()
{
	Array2D a(3,3);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			cout<<"a["<<i<<"]["<<j<<"] = ";
			cin>>a[i][j];
		}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}