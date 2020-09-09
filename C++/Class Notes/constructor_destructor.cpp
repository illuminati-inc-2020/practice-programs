#include <iostream>

using namespace std;

class TestClass
{
	int i;
public:
	TestClass(const TestClass &ob)
	{
		TestClass::i=ob.i+1;
		cout << "copy const" << endl;
	}
	TestClass()
	{
		cout << "def const" << endl;
	}
	TestClass(int i)
	{
		cout << "const" << i << endl;
		TestClass::i=i;
	}
	~TestClass()
	{
		cout << "dest" << i << endl;
	}
};

main()
{
	cout << "line1" << endl;
	TestClass obj1=10;				//Initializing constructor
	cout << "line2" << endl;
	TestClass obj2=obj1;				//Copy Constructor
	TestClass obj3=13;				//Default constructor
	//obj3=obj1;					//Assignment operator
	cout << "line3" << endl;
}
