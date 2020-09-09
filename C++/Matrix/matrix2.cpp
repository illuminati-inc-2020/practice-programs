/**
 * Author		:	Rakesh Malik
 * Date			:	12/09/2011
 * Class		:	Matrix
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

class Matrix
{
	Array2D *mat;
public:
	Matrix(int,int);
	Matrix(const Matrix&);
	int getRows();
	int getColumns();
	int& element(int,int);
};
inline Matrix::Matrix(int m,int n)
{
	Matrix::mat=new Array2D(m,n);
	for(int i=0;i<Matrix::mat->getRows();i++)
		for(int j=0;j<Matrix::mat->getColumns();j++)
			(*Matrix::mat)[i][j]=0;
}
inline Matrix::Matrix(const Matrix& a)
{
	Matrix::mat=new Array2D(a.mat->getRows(),a.mat->getColumns());
	for(int i=0;i<Matrix::mat->getRows();i++)
		for(int j=0;j<Matrix::mat->getColumns();j++)
			(*Matrix::mat)[i][j]=(*a.mat)[i][j];
}
inline int Matrix::getRows()
{
	return Matrix::mat->getRows();
}
inline int Matrix::getColumns()
{
	return Matrix::mat->getColumns();
}
inline int& Matrix::element(int m,int n)
{
	return (*Matrix::mat)[m][n];
}
inline Matrix operator+(Matrix a,Matrix b)
{
	if(a.getRows()==b.getRows() && a.getColumns()==b.getColumns())
	{
		Matrix c(a.getRows(),a.getColumns());
		for(int i=0;i<c.getRows();i++)
			for(int j=0;j<c.getColumns();j++)
			{
				c.element(i,j)=a.element(i,j)+b.element(i,j);
			}
		return c;
	}
}
ostream& operator<<(ostream& out,Matrix a)
{
	for(int i=0;i<a.getRows();i++)
	{
		for(int j=0;j<a.getColumns();j++)
			cout<<a.element(i,j)<<"\t";
		cout<<endl;
	}
	return out;
}

main()
{
	Matrix a(3,3);
	for(int i=0;i<a.getRows();i++)
		for(int j=0;j<a.getColumns();j++)
		{
			cout<<"a("<<i<<","<<j<<") = ";
			cin>>a.element(i,j);
		}
	cout<<a+a;
}
