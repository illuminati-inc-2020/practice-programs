#include <iostrean>

using namespace std;

class TestClass
{
	int i;
public:
	int &get_i();
};

int &TestClass::get_i()
{
	return TestClass::i;
}

main()
{
	TestClass x;
	x.get_i()=10;
	cout << x.get_i() << endl;
}
