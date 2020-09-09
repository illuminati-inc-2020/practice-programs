#include <iostream>

using namespace std;

class Test
{
	int i;
public:
	Test(){}
	Test(int i);
	int get_i();
//	Test operator+(Test x);
friend	Test operator+(Test x,Test y);
};

Test::Test(int i)
{
	Test::i=i;
}
int Test::get_i()
{
	return Test::i;
}
/*Test Test::operator+(Test x)
{
	Test y;
	y.i=Test::i+x.i;
	return y;
}
*/
Test operator+(Test x,Test y)
{
	Test z;
	z.i=x.i+y.i;
	return z;
}

main()
{
	Test a=10,b=20,c;
	c=20+b;
	cout << c.get_i() << endl;
}
