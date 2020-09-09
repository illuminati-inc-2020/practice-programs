#include <iostream>

using namespace std;

class TestClass
{
	int i;
public:
	int &get_i();
	TestClass()
	{
		cout << "Constructor" << endl;
	}
	TestClass(const TestClass &x)
	{
		cout << "Copy Constructor" << endl;
	}
	~TestClass()
	{
		cout << "Destructor" << endl;
	}
	TestClass operator=(TestClass x)
	{
		return *this;
	}
};

int &TestClass::get_i()
{
	return TestClass::i;
}

//TestClass x;
TestClass fnc()
{
	TestClass x;
	/* Copy constructor for anonymous TestClass object */
	return x;
	/* destructor for anonymous TestClass object */
}

main()
{
	/* Constructor for a */
	cout << "line1" << endl;
	fnc();
	cout << "line2" << endl;
	/* Destructor for x */
}
