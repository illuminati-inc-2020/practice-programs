#include <iostream>

using namespace std;

class A
{
	int i;
public:
	A(){cout << "Const A" << endl;}
	~A(){cout << "Dest A" << endl;}
};

class B:public A
{
public:
	B(){cout << "Const B" << endl;}
	~B(){cout << "Dest B" << endl;}
};

main()
{
	B obj;
}
