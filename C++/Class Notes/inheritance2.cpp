/* Passing parameter to base class constructor */

#include <iostream>

using namespace std;

class A
{
private:
	int i;
public:
	A(int i){A::i=i;}
	void display(){cout<<i<<endl;}
};

class B:public A
{
public:
	B(int t):A(t){}
};

main()
{
	B obj=10;
	obj.display();
}
