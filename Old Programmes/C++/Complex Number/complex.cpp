/**
 * Author		:	Rakesh Malik
 * Date			:	02/08/2011
 * Class		:	Complex Number
 */

#include <iostream>
#include <cmath>

using namespace std;

class Complex
{
	double real;
	double imaginary;
public:
	Complex();
	Complex(double,double);
	void setReal(double);
	void setImaginary(double);
	double getReal();
	double getImaginary();
};

inline Complex::Complex()
{
	Complex::real=0;
	Complex::imaginary=0;
}
inline Complex::Complex(double real,double imaginary)
{
	Complex::real=real;
	Complex::imaginary=imaginary;
}
inline void Complex::setReal(double real)
{
	Complex::real=real;
}
inline void Complex::setImaginary(double imaginary)
{
	Complex::imaginary=imaginary;
}
inline double Complex::getReal()
{
	return Complex::real;
}
inline double Complex::getImaginary()
{
	return Complex::imaginary;
}

Complex add(Complex z1,Complex z2)
{
	Complex z;
	z.setReal(z1.getReal()+z2.getReal());
	z.setImaginary(z1.getImaginary()+z2.getImaginary());
	return z;
}
Complex sub(Complex z1,Complex z2)
{
	Complex z;
	z.setReal(z1.getReal()-z2.getReal());
	z.setImaginary(z1.getImaginary()-z2.getImaginary());
	return z;
}
Complex mul(Complex z1,Complex z2)
{
	Complex z;
	z.setReal(z1.getReal()*z2.getReal()-z1.getImaginary()*z2.getImaginary());
	z.setImaginary(z1.getReal()*z2.getImaginary()+z1.getImaginary()*z2.getReal());
	return z;
}
double mod(Complex z)
{
	return sqrt(z.getReal()*z.getReal()+z.getImaginary()*z.getImaginary());
}
Complex div(Complex z1,Complex z2)
{
	Complex z;
	z.setReal((z1.getReal()*z2.getReal()+z1.getImaginary()*z2.getImaginary())/mod(z2));
	z.setImaginary((z1.getImaginary()*z2.getReal()-z1.getReal()*z2.getImaginary())/mod(z2));
	return z;
}

main()
{
	Complex z,z1(3,4),z2(7,8);
	cout << "z = " << z.getReal() << " + " << z.getImaginary() << "i" << endl;
	cout << "z1 = " << z1.getReal() << " + " << z1.getImaginary() << "i" << endl;
	cout << "z2 = " << z2.getReal() << " + " << z2.getImaginary() << "i" << endl;
	z=add(z1,z2);
	cout << "z1+z2 = " << z.getReal() << " + " << z.getImaginary() << "i" << endl;
	z=sub(z1,z2);
	cout << "z1-z2 = " << z.getReal() << " + " << z.getImaginary() << "i" << endl;
	z=mul(z1,z2);
	cout << "z1*z2 = " << z.getReal() << " + " << z.getImaginary() << "i" << endl;
	z=div(z1,z2);
	cout << "z1/z2 = " << z.getReal() << " + " << z.getImaginary() << "i" << endl;
	cout << "|z1| = " << mod(z1) << endl;
	cout << "|z2| = " << mod(z2) << endl;
}
