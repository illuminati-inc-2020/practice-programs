#include <iostream>

using namespace std;

class X {
	int i;
public:
	X(int i) {
		X::i=i;
	}
	operator int();				//must be non-static member function
	//friend operator int(X);
};
/*operator int(X x) {
	return x.i;
}*/
X::operator int() {
	return X::i;
}

main() {
	X x=5;
	cout<<(int)x<<endl;
}
