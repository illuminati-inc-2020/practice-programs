#include <iostream>

using namespace std;

void inr(int &x)	//int &x=i
{
	x++;
}

main()
{
	int i=10,j=20;
	cout << i << endl
	     << j << endl;
	inr(i);
	inr(j);
	cout << i << endl
	     << j << endl;
}
