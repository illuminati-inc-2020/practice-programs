#include <iostream>
#include <iomanip>

using namespace std;

class Exception
{
	int err_no;
	string msg;
public:
	Exception(int,string);
	int getErrorNumber();
	string getMessage();
};
Exception::Exception(int err_no,string msg)
{
	Exception::err_no=err_no;
	Exception::msg=msg;
}
int Exception::getErrorNumber()
{
	return Exception::err_no;
}
string Exception::getMessage()
{
	return Exception::msg;
}
class InvalidMatrixOrderException : public Exception {
public:
	InvalidMatrixOrderException() : Exception(100, "Invalid Matrix Order Exception"){}
};
class InvalidMatrixAdditionException : public Exception {
public:
	InvalidMatrixAdditionException() : Exception(101, "Invalid Matrix Addition Exception"){}
};
class InvalidMatrixMultiplitionException : public Exception {
public:
	InvalidMatrixMultiplitionException() : Exception(102, "Invalid Matrix Multiplication Exception"){}
};

class Matrix {
	int m, n;
	double **buf;
public:
	Matrix(int, int);
	Matrix(const Matrix&);
	~Matrix();
	double& operator()(int, int);
	Matrix operator+(Matrix);
	Matrix operator*(Matrix);
	friend ostream& operator<<(ostream&, Matrix);
};
Matrix::Matrix(int m, int n) {
	if(m>0 && n>0) {
		Matrix::m=m;
		Matrix::n=n;
		try {
			Matrix::buf=new double*[m];
			for(int i=0; i<m; i++) {
				Matrix::buf[i]=new double[n];
				for(int j=0; j<n; j++)
					Matrix::buf[i][j]=0;
			}
		} catch(bad_alloc e) {
			cerr<<"ERROR : bad_alloc during Matrix allocation"<<endl;
		}
	}
	else
		throw InvalidMatrixOrderException();
}
Matrix::Matrix(const Matrix&A) {
	Matrix::m=A.m;
	Matrix::n=A.n;
	try {
		Matrix::buf=new double*[A.m];
		for(int i=0; i<m; i++) {
			Matrix::buf[i]=new double[A.n];
			for(int j=0; j<n; j++)
				Matrix::buf[i][j]=A.buf[i][j];
		}
	} catch(bad_alloc e) {
		cerr<<"ERROR : bad_alloc during Matrix allocation"<<endl;
	}
}
Matrix::~Matrix() {
	for(int i=0; i<Matrix::m; i++)
		delete Matrix::buf[i];
	delete Matrix::buf;
}
double& Matrix::operator()(int i, int j) {
	return Matrix::buf[i][j];
}
Matrix Matrix::operator+(Matrix A) {
	if(Matrix::m!=A.m || Matrix::n!=A.n)
		throw InvalidMatrixAdditionException();
	Matrix B(A.m, A.n);
	for(int i=0; i<Matrix::m; i++) 
		for(int j=0; j<Matrix::n; j++)
			B.buf[i][j]=Matrix::buf[i][j]+A.buf[i][j];
	return B;
}
Matrix Matrix::operator*(Matrix A) {
	if(Matrix::n!=A.m)
		throw InvalidMatrixMultiplitionException();
	Matrix B(Matrix::m, A.n);
	for(int i=0; i<Matrix::m; i++)
		for(int j=0; j<Matrix::n; j++)
			for(int k=0; k<A.n; k++)
				B.buf[i][k]+=Matrix::buf[i][j]*A.buf[j][k];
	return B;
}
ostream& operator<<(ostream& os, Matrix A) {
	for(int i=0; i<A.m; i++) {
		for(int j=0; j<A.n; j++)
			os<<setw(5)<<A.buf[i][j]<<" ";
		os<<endl;
	}
	return os;
}

main() {
	Matrix A(3, 2), B(2, 1);
	A(0, 0)=1;
	A(0, 1)=2;
	A(1, 0)=3;
	A(1, 1)=4;
	A(2, 0)=5;
	A(2, 1)=6;
	B(0, 0)=1;
	B(1, 0)=2;
	cout<<A<<endl
	    <<B<<endl
	    <<A*B<<endl;
}
