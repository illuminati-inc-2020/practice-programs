#include <iostream>
using namespace std;

class B								// Abstract class
{
public:
	virtual void display()=0;				// Pure virtual function
};

class D1:public B
{
public:
	void display(){cout<<"Message from class D1"<<endl;}
};

class D2:public B						// Abstract Class
{
};

void fnc(B &obj)
{
	obj.display();
}

main()
{
	D1 obj1;
	D2 obj2;	//ERROR
	fnc(obj1);
	fnc(obj2);
}
