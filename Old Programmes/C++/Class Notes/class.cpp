#include <iostream>

using namespace std;

class TestClass
{
	int x;
public:
	void setX(int);
	int getX();
};
inline void TestClass::setX(int x)
{
	TestClass::x=x;
}
inline int TestClass::getX()
{
	return TestClass::x;
}

main()
{
	TestClass obj;
	obj.setX(10);
	cout << obj.getX() << endl;
}
