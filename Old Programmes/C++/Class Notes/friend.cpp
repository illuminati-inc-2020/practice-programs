#include <iostream>

using namespace std;

class TestClass
{
	int i;
public:
	int j;
protected:
	int k;
friend 	void fnc();
};

void fnc()
{
	TestClass x;
	x.i=10;
	x.j=20;
	x.k=30;
}

main()
{
	fnc();
}
