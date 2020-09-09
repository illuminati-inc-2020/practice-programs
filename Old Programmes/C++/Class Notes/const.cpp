#include <iostream>

using namespace std;

main() {
	const int *ci=new int;
	int *i=const_cast<int*>(ci);
	*i=20;
	cout<<*i<<endl;
	cout<<*ci<<endl;
}
