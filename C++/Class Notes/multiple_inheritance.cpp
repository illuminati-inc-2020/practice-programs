#include <iostream>

using namespace std;

class W
{
public:
	int i;
};
class X:public W {};
class Y:public W {};
class Z:public X,public Y {};

main()
{
	Z obj;
	obj.X::i=10;
	cout << obj.Y::i;
}
