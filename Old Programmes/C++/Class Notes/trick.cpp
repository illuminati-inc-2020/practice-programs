#include <iostream>

using namespace std;

class X {
	int i;
public:
	void display() {
		cout<<i<<endl;
	}
	int operator&() {
		return 999;
	}
	Y* address() {
		return this;
	}
};

main() {
	X a;
	int *b=(int*)a.address();
	*b=10;
	a.display();
}
