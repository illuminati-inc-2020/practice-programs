#include <iostream>

using namespace std;

class Test {
	int i;
public:
	int operator&() {
		return 10;
	}
};

main() {
	Test a;
	cout<<&a<<endl;
}
